#version 330 core

struct PointLight {
    vec3 position;
    vec3 color;
};


struct DirectionalLight {
    vec3 direction;
    vec3 color;
};

out vec4 FragColor;

in vec3 FragPos;  
in vec3 Normal;  
in vec3 Tangent;  
in vec3 BiTangent;  
in vec2 vertex_uv;
  
uniform vec3 viewPos;

uniform int dirLightCount;
uniform int pointLightCount;

vec2 UV;
vec3 F0;

vec3 albedo;
float metallic;
float roughness;

uniform sampler2D albedoMap;
uniform sampler2D metallicMap;
uniform sampler2D roughnessMap;
uniform sampler2D normalMap;
uniform sampler2D depthMap;

#define MAX_DIRECTIONAL_LIGHT 8
#define MAX_POINT_LIGHT 8
#define PI 3.141592653589793

// Uniforms
uniform DirectionalLight dirLights[MAX_DIRECTIONAL_LIGHT];
uniform PointLight pointLights[MAX_POINT_LIGHT];

float DistributionGGX(vec3 N, vec3 H, float roughness)
{
    float a = roughness*roughness;
    float a2 = a*a;
    float NdotH = max(dot(N, H), 0.0);
    float NdotH2 = NdotH*NdotH;

    float nom   = a2;
    float denom = (NdotH2 * (a2 - 1.0) + 1.0);
    denom = PI * denom * denom;

    return nom / denom;
}
// ----------------------------------------------------------------------------
float GeometrySchlickGGX(float NdotV, float roughness)
{
    float r = (roughness + 1.0);
    float k = (r*r) / 8.0;

    float nom   = NdotV;
    float denom = NdotV * (1.0 - k) + k;

    return nom / denom;
}
// ----------------------------------------------------------------------------
float GeometrySmith(vec3 N, vec3 V, vec3 L, float roughness)
{
    float NdotV = max(dot(N, V), 0.0);
    float NdotL = max(dot(N, L), 0.0);
    float ggx2 = GeometrySchlickGGX(NdotV, roughness);
    float ggx1 = GeometrySchlickGGX(NdotL, roughness);

    return ggx1 * ggx2;
}
// ----------------------------------------------------------------------------
vec3 fresnelSchlick(float cosTheta, vec3 f0)
{
    return f0 + (1.0 - f0) * pow(clamp(1.0 - cosTheta, 0.0, 1.0), 5.0);
}

vec3 light(vec3 light, vec3 view, vec3 normal, vec3 lightColor) {
    vec3 halfVec = normalize(light + view);

    float D = DistributionGGX(normal, halfVec, roughness);
    float G = GeometrySmith(normal, view, light, roughness);
    vec3 F = fresnelSchlick(max(dot(halfVec, view), 0.0), F0);

    vec3 kS = F;

    vec3 kD = vec3(1.0) - kS;

    kD *= 1.0 - metallic;
    
    float NdotL = max(dot(normal, light), 0.0);

    vec3 diffuse = albedo/PI;
    vec3 numerator = D * G * F;
    float denominator = 4.0 * max(dot(normal, view), 0.0) * max(dot(normal, light), 0.0) + 0.0001; // + 0.0001 to prevent divide by zero
    vec3 specular = numerator / denominator;

    return (kD*diffuse + kS*specular) * NdotL * lightColor;
}

vec2 ParallaxMapping(vec3 viewDir, vec3 normal, vec3 tangent, vec3 biTangent)
{ 

    float heightScale = 0.05;
    // number of depth layers
    const float minLayers = 8;
    const float maxLayers = 32;
    float numLayers = mix(maxLayers, minLayers, abs(dot(normal, viewDir)));  
    // calculate the size of each layer
    float layerDepth = 1.0 / numLayers;
    // depth of current layer
    float currentLayerDepth = 0.0;
    // the amount to shift the texture coordinates per layer (from vector P)
    vec2 P = vec2(dot(tangent, viewDir), dot(biTangent, viewDir)) / dot(normal, viewDir) * heightScale; 
    vec2 deltaTexCoords = P / numLayers;
  
    // get initial values
    vec2  currentTexCoords = vertex_uv;
    float currentDepthMapValue = texture(depthMap, currentTexCoords).r;
      
    while(currentLayerDepth < currentDepthMapValue)
    {
        // shift texture coordinates along direction of P
        currentTexCoords -= deltaTexCoords;
        // get depthmap value at current texture coordinates
        currentDepthMapValue = texture(depthMap, currentTexCoords).r;
        // get depth of next layer
        currentLayerDepth += layerDepth;  
    }
    
    // get texture coordinates before collision (reverse operations)
    vec2 prevTexCoords = currentTexCoords + deltaTexCoords;

    // get depth after and before collision for linear interpolation
    float afterDepth  = currentDepthMapValue - currentLayerDepth;
    float beforeDepth = texture(depthMap, prevTexCoords).r - currentLayerDepth + layerDepth;
 
    // interpolation of texture coordinates
    float weight = afterDepth / (afterDepth - beforeDepth);
    vec2 finalTexCoords = prevTexCoords * weight + currentTexCoords * (1.0 - weight);
    
    return finalTexCoords;
}


void main()
{
    F0 = mix(vec3(0.04), albedo, metallic);

    //variables
    
    vec3 result = vec3(0.0);
    vec3 view = normalize(viewPos-FragPos);
    vec3 normal = normalize(Normal);
    vec3 tangent = normalize(Tangent);
    vec3 biTangent = normalize(BiTangent);

    //depthMap
    UV = vertex_uv;
    UV = ParallaxMapping(view, normal, tangent, biTangent);

    //normal Map
    mat3 TBN = mat3(tangent, biTangent, normal);
    normal = 2 * TBN * (texture2D(normalMap, UV).xyz - 0.5f);
    normal = normalize(normal);

    albedo = pow(texture(albedoMap, UV).rgb, vec3(2.2));
    metallic = texture(metallicMap, UV).r;
    roughness = texture(roughnessMap, UV).r;


    
    for(int i = 0; i < dirLightCount; i++) {
        vec3 lightDir = normalize(dirLights[i].direction);
        float attenuation = 1.0;
        result += light(lightDir, view, normal, dirLights[i].color) * attenuation;
    }
    
    for(int i = 0; i < pointLightCount; i++) {
        vec3 lightDir = normalize(pointLights[i].position - FragPos);
        float attenuation = 1.0/pow(length(pointLights[i].position - FragPos), 2.0);
        result += light(lightDir, view, normal, pointLights[i].color) * attenuation;
    }

    
    // ambient lighting (we now use IBL as the ambient term)
    vec3 ambient = vec3(0.03) * albedo* 1.0;
    
    vec3 color = ambient + result;

    // HDR tonemapping
    color = color / (color + vec3(1.0));
    // gamma correct
    color = pow(color, vec3(1.0/2.2));

    //color = vec3(UV, 0.0);
    FragColor = vec4(color, texture2D(albedoMap, UV).a);
} 
