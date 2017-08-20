#include "MayhemObject.h"


std::atomic<unsigned _int32> MayhemObject::s_uniqueId;

MayhemObject::MayhemObject(): m_uniqueId(++s_uniqueId)
{
	std::cout << m_uniqueId << std::endl;

	//m_handleIndex = FindFreeSlotInHandleTable();

	if (m_handleIndex < 0) {
		std::cout << "ERROR Creating Object: Max Objects created" << std::endl;
		return;
	}

	m_mesh = {
		-0.5f, -0.5f, -0.5f,  0.0f, 0.0f,
		0.5f, -0.5f, -0.5f,  1.0f, 0.0f,
		0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
		0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
		-0.5f,  0.5f, -0.5f,  0.0f, 1.0f,
		-0.5f, -0.5f, -0.5f,  0.0f, 0.0f,

		-0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
		0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
		0.5f,  0.5f,  0.5f,  1.0f, 1.0f,
		0.5f,  0.5f,  0.5f,  1.0f, 1.0f,
		-0.5f,  0.5f,  0.5f,  0.0f, 1.0f,
		-0.5f, -0.5f,  0.5f,  0.0f, 0.0f,

		-0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
		-0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
		-0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
		-0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
		-0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
		-0.5f,  0.5f,  0.5f,  1.0f, 0.0f,

		0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
		0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
		0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
		0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
		0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
		0.5f,  0.5f,  0.5f,  1.0f, 0.0f,

		-0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
		0.5f, -0.5f, -0.5f,  1.0f, 1.0f,
		0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
		0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
		-0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
		-0.5f, -0.5f, -0.5f,  0.0f, 1.0f,

		-0.5f,  0.5f, -0.5f,  0.0f, 1.0f,
		0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
		0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
		0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
		-0.5f,  0.5f,  0.5f,  0.0f, 0.0f,
		-0.5f,  0.5f, -0.5f,  0.0f, 1.0f
	};

	m_position = glm::vec3(0.0f, 0.0f, 0.0f);

	glGenVertexArrays(1, &m_VAO);
	glGenBuffers(1, &m_VBO);

	glBindVertexArray(m_VAO);

	glBindBuffer(GL_ARRAY_BUFFER, m_VBO);
	glBufferData(GL_ARRAY_BUFFER, m_mesh.size() * sizeof(m_mesh), &m_mesh[0], GL_STATIC_DRAW);

	// position attribute
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);
	// texture coord attribute
	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)(3 * sizeof(float)));
	glEnableVertexAttribArray(1);

	m_shader = new Shader("Shaders/stdShader.vs", "Shaders/stdShader.fs");
}

MayhemObject::~MayhemObject()
{
	delete m_shader;
	m_shader = NULL;
}

void MayhemObject::LoadTexture(const char* filePath) {
	if (filePath == "") {
		if (m_textureLoc == "") {
			std::cout << "ERROR LOADING TEXTURE: no texture selected";
			return;
		}
		else {
			filePath = m_textureLoc;
		}
	}

	glGenTextures(1, &m_texture);
	glBindTexture(GL_TEXTURE_2D, m_texture);
	// set the texture wrapping parameters
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	// set texture filtering parameters
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	// load image, create texture and generate mipmaps
	int width, height, nrChannels;
	stbi_set_flip_vertically_on_load(true); // tell stb_image.h to flip loaded texture's on the y-axis.
	unsigned char *data = stbi_load(filePath, &width, &height, &nrChannels, 0);
	if (data)
	{
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
		glGenerateMipmap(GL_TEXTURE_2D);
	}
	else
	{
		std::cout << "Failed to load texture" << std::endl;
	}
	stbi_image_free(data);
	m_shader->Use();
	m_shader->SetInt("texture", 0);
}


void MayhemObject::Update(double dt) {

	if (this->m_isEnabled) {

	}
}

void MayhemObject::SetEnabled(bool enabled) {
	this->m_isEnabled = enabled;
}


void MayhemObject::Render(const glm::mat4 projection, const glm::mat4 view) {
	glActiveTexture(GL_TEXTURE);
	glBindTexture(GL_TEXTURE_2D, m_texture);

	m_shader->Use();

	m_shader->SetMat4("projection", projection); // note: currently we set the projection matrix each frame, but since the projection matrix rarely changes it's often best practice to set it outside the main loop only once.
	m_shader->SetMat4("view", view);

	glBindVertexArray(m_VAO);

	m_model = glm::translate(m_model, glm::sin(m_position));
	m_shader->SetMat4("model", m_model);

	glDrawArrays(GL_TRIANGLES, 0, 36);
}

void MayhemObject::SetPosition(const glm::vec3 position) {
	m_position = position;
}

glm::mat4 MayhemObject::GetModel() const {
	return m_model;
}

int MayhemObject::FindFreeSlotInHandleTable() {
	//for (unsigned _int32 i = 0; i < MAX_GAME_OBJECTS; i++) {
	//	if (g_apGameObject[i] == NULL) {
		//	g_apGameObject[i] = this;
	//		return i;
	//	}
//	}
	return -1;
}