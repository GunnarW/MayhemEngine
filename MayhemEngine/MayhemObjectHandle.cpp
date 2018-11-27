#include "MayhemObjectHandle.h"


// creates a reference to object in MayhemObjects
MayhemObjectHandle::MayhemObjectHandle(MayhemObjects* mayhemObjects, unsigned _int32 handleIndex) :
	m_mayhemObjects(mayhemObjects), m_handleIndex(handleIndex)
{
	m_uniqueId = m_mayhemObjects->m_uniqueId[m_handleIndex];
	std::cout << "Unique ID: " << m_uniqueId << std::endl;
}

MayhemObjectHandle::~MayhemObjectHandle()
{
}

// Checks if the object exists
bool MayhemObjectHandle::ObjectExists() const {
	return m_mayhemObjects->m_uniqueId[m_handleIndex] == m_uniqueId;
}

void MayhemObjectHandle::Update(double DT)
{
	//m_mayhemObjects->m_renderable[m_handleIndex].SetPosition(m_mayhemObjects->m_position);
}

///////////////////////////// Setters ///////////////////////////////////////
bool MayhemObjectHandle::SetEnabled(const bool enabled) {
	if (ObjectExists()) {
		m_mayhemObjects->m_enabled[m_handleIndex] = enabled;
		return true;
	}
	return false;
}

bool MayhemObjectHandle::SetPosition(const glm::vec3 pos) {
	if (ObjectExists()) {
		m_mayhemObjects->m_position[m_handleIndex] = pos;
		std::cout << m_mayhemObjects->m_position[m_handleIndex].x << m_mayhemObjects->m_position[m_handleIndex].y << m_mayhemObjects->m_position[m_handleIndex].z << std::endl;
		return true;
	}
	return false;
}

bool MayhemObjectHandle::SetRotation(const glm::quat rot) {
	if (ObjectExists()) {
		m_mayhemObjects->m_rotation[m_handleIndex] = rot;
		return true;
	}
	return false;
}


bool MayhemObjectHandle::SetDirection(const glm::vec3 dir) {
	if (ObjectExists()) {
		m_mayhemObjects->m_direction[m_handleIndex] = dir;
		return true;
	}
	return false;
}

bool MayhemObjectHandle::SetAmbient(const glm::vec3 amb) {
	if (ObjectExists()) {
		m_mayhemObjects->m_ambient[m_handleIndex] = amb;
		return true;
	}
	return false;
}

bool MayhemObjectHandle::SetDiffuse(const glm::vec3 diff) {
	if (ObjectExists()) {
		m_mayhemObjects->m_diffuse[m_handleIndex] = diff;
		return true;
	}
	return false;
}

bool MayhemObjectHandle::SetSpecular(const glm::vec3 spec) {
	if (ObjectExists()) {
		m_mayhemObjects->m_specular[m_handleIndex] = spec;
		return true;
	}
	return false;
}

bool MayhemObjectHandle::SetConstant(const float constant) {
	if (ObjectExists()) {
		m_mayhemObjects->m_constant[m_handleIndex] = constant;
		return true;
	}
	return false;
}
bool MayhemObjectHandle::SetLinear(const float linear) {
	if (ObjectExists()) {
		m_mayhemObjects->m_linear[m_handleIndex] = linear;
		return true;
	}
	return false;
}
bool MayhemObjectHandle::SetQuadratic(const float quad) {
	if (ObjectExists()) {
		m_mayhemObjects->m_quadratic[m_handleIndex] = quad;
		return true;
	}
	return false;
}
bool MayhemObjectHandle::SetCutOff(const float cut) {
	if (ObjectExists()) {
		m_mayhemObjects->m_cutOff[m_handleIndex] = cut;
		return true;
	}
	return false;
}
bool MayhemObjectHandle::SetOuterCutOff(const float cut) {
	if (ObjectExists()) {
		m_mayhemObjects->m_outerCutOff[m_handleIndex] = cut;
		return true;
	}
	return false;
}

bool MayhemObjectHandle::AddMesh(const Mesh mesh)
{
	if (ObjectExists()) {
		m_mayhemObjects->m_meshes[m_handleIndex].push_back(mesh);
		return true;
	}
	return false;
}
bool MayhemObjectHandle::AddTexture(const Texture texture)
{
	if (ObjectExists()) {
		m_mayhemObjects->m_texturesLoaded[m_handleIndex].push_back(texture);

		return true;
	}
	return false;
}
bool MayhemObjectHandle::SetDirectory(const std::string directory)
{
	if (ObjectExists()) {
		m_mayhemObjects->m_directories[m_handleIndex] = directory;
		return true;
	}
	return false;
}

bool MayhemObjectHandle::SetTransform(const glm::mat4 transform)
{
	if (ObjectExists()) {
		m_mayhemObjects->m_transforms[m_handleIndex] = transform;
		return true;
	}
	return false;
}

bool MayhemObjectHandle::SetShader(const Shader shader)
{
	if (ObjectExists()) {
		m_mayhemObjects->m_shaders[m_handleIndex] = shader;
		return true;
	}
	return false;
}
///////////////////// Getters ///////////////////////////////////////////////////

bool MayhemObjectHandle::IsEnabled() const 
{
	if (ObjectExists()) {
		return m_mayhemObjects->m_enabled[m_handleIndex];
	}
}

glm::vec3 MayhemObjectHandle::GetPosition() const 
{
	if (ObjectExists()) {
		return m_mayhemObjects->m_position[m_handleIndex];
	}
}

glm::quat MayhemObjectHandle::GetRotation() const 
{
	if (ObjectExists()) {
		return m_mayhemObjects->m_rotation[m_handleIndex];
	}
}


glm::vec3 MayhemObjectHandle::GetDirection() const 
{
	if (ObjectExists()) {
		return m_mayhemObjects->m_direction[m_handleIndex];
	}
}
glm::vec3 MayhemObjectHandle::GetAmbient() const 
{
	if (ObjectExists()) {
		return m_mayhemObjects->m_ambient[m_handleIndex];
	}
}
glm::vec3 MayhemObjectHandle::GetDiffuse() const 
{
	if (ObjectExists()) {
		return m_mayhemObjects->m_diffuse[m_handleIndex];
	}
}
glm::vec3 MayhemObjectHandle::GetSpecular() const 
{
	if (ObjectExists()) {
		return m_mayhemObjects->m_specular[m_handleIndex];
	}
}

float MayhemObjectHandle::GetConstant() const 
{
	if (ObjectExists()) {
		return m_mayhemObjects->m_constant[m_handleIndex];
	}
}
float MayhemObjectHandle::GetLinear() const 
{
	if (ObjectExists()) {
		return m_mayhemObjects->m_linear[m_handleIndex];
	}
}
float MayhemObjectHandle::GetQuadratic() const 
{
	if (ObjectExists()) {
		return m_mayhemObjects->m_quadratic[m_handleIndex];
	}
}
float MayhemObjectHandle::GetCutOff() const 
{
	if (ObjectExists()) {
		return m_mayhemObjects->m_cutOff[m_handleIndex];
	}
}
float MayhemObjectHandle::GetOuterCutOff() const 
{
	if (ObjectExists()) {
		return m_mayhemObjects->m_outerCutOff[m_handleIndex];
	}
}

std::vector<Mesh>* MayhemObjectHandle::GetMeshes() const
{
	if (ObjectExists()) {
		return &m_mayhemObjects->m_meshes[m_handleIndex];
	}
}

std::vector<Texture>* MayhemObjectHandle::GetTextures() const
{
	if (ObjectExists()) {
		return &m_mayhemObjects->m_texturesLoaded[m_handleIndex];
	}
}

std::string MayhemObjectHandle::GetDirectory() const
{
	if (ObjectExists()) {
		return m_mayhemObjects->m_directories[m_handleIndex];
	}
}

glm::mat4 MayhemObjectHandle::GetTransform() const
{
	if (ObjectExists()) {
		return m_mayhemObjects->m_transforms[m_handleIndex];
	}
}

Shader* MayhemObjectHandle::GetShader() const
{
	if (ObjectExists()) {
		return &m_mayhemObjects->m_shaders[m_handleIndex];
	}
}