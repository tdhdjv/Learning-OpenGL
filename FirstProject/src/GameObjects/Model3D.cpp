#include "Model3D.h"

const VertexBufferLayout Vertex3D::layout = []{
	VertexBufferLayout layout;
	layout.push<float>(3);
	layout.push<float>(2);
	layout.push<float>(3);
	layout.push<float>(3);
	return layout;
}();