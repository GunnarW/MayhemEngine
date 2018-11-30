#pragma once
#include "MayhemObjects.h"

class MayhemObjectHandle
{
public:
	explicit MayhemObjectHandle(MayhemObjects* mayhemObjects, unsigned _int32 handleIndex);

	~MayhemObjectHandle();

	bool ObjectExists() const;

	void Update(double);

	// Setters
	bool SetEnabled(const bool);
	bool SetPosition(const glm::vec3);
	bool SetRotation(const glm::quat);

	bool SetConstant(const float);
	bool SetLinear(const float);
	bool SetQuadratic(const float);
	bool SetCutOff(const float);
	bool SetOuterCutOff(const float);
	
	bool SetTransform(const glm::mat4);
	bool SetShader(const Shader);

	bool SetDirection(const glm::vec3);
	bool SetAmbient(const glm::vec3);
	bool SetDiffuse(const glm::vec3);
	bool SetSpecular(const glm::vec3);

	virtual bool AddMesh(const Mesh) { return false; }
	virtual bool AddTexture(const Texture) { return false; }
	virtual bool SetDirectory(const std::string) { return false; }

	// Getters
	bool IsEnabled() const;
	glm::vec3 GetPosition() const;
	glm::quat GetRotation() const;

	glm::vec3 GetDirection() const;

	float GetConstant() const;
	float GetLinear() const;
	float GetQuadratic() const;
	float GetCutOff() const;
	float GetOuterCutOff() const;
	
	glm::mat4 GetTransform() const;
	Shader* GetShader() const;

	glm::vec3 GetAmbient() const;
	glm::vec3 GetDiffuse() const;
	glm::vec3 GetSpecular() const;

	virtual std::vector<Mesh>* GetMeshes() const { return nullptr; }
	virtual std::vector<Texture>* GetTextures() const { return nullptr; };
	virtual std::string GetDirectory() const { return nullptr; };

protected:
	unsigned _int32 m_uniqueId;
	unsigned _int32 m_handleIndex;
	MayhemObjects* m_mayhemObjects;
};

