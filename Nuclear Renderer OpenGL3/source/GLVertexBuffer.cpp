#include <NuclearRendererOGL3\GLVertexBuffer.h>
#include <NuclearRendererBase/NRBInputLayout.h>
#include <NuclearCommon\Common_API_Types.h>
using namespace NuclearEngine;
namespace NuclearRenderer {
	GLenum GetGLDataType(DataType dataType);
	unsigned int GetComponentCount(DataType dataType);

	GLVertexBuffer::GLVertexBuffer() 
	{

	}

	GLVertexBuffer::~GLVertexBuffer()
	{
		
	}

	void GLVertexBuffer::Delete()
	{
		glDeleteBuffers(1, &VertexBuffer);
		glDeleteBuffers(1, &VAO);
	}

	void GLVertexBuffer::Create(const void* data, unsigned int size, NuclearEngine::BufferGPUUsage usage, NuclearEngine::BufferCPUAccess access)
	{
		glGenVertexArrays(1, &VAO);
		glBindVertexArray(0);

		glGenBuffers(1, &VertexBuffer);
		glBindBuffer(GL_ARRAY_BUFFER, VertexBuffer);
		if (usage == NuclearEngine::BufferGPUUsage::Static)
		{
			glBufferData(GL_ARRAY_BUFFER, size, data, GL_STATIC_DRAW);
		}
		else
		{
			glBufferData(GL_ARRAY_BUFFER, size, data, GL_DYNAMIC_DRAW);
		}
		glBindBuffer(GL_ARRAY_BUFFER, 0);

	}

	void GLVertexBuffer::Update(const void * data, unsigned int size)
	{
		glBindBuffer(GL_ARRAY_BUFFER, this->VertexBuffer);
		glBufferSubData(GL_ARRAY_BUFFER, 0, size, data);
		glBindBuffer(GL_ARRAY_BUFFER, 0);
	}

	void GLVertexBuffer::SetInputLayout(NRBInputLayout * layout, NRBShader * shader)
	{
		unsigned int index = 0;
		glBindVertexArray(VAO);
		glBindBuffer(GL_ARRAY_BUFFER, VertexBuffer);

		for (size_t i = 0; i < layout->GetBufferElement().size(); i++)
		{
			glEnableVertexAttribArray(index);
			glVertexAttribPointer(index,
				GetComponentCount(layout->GetBufferElement()[i].dataType),
				GetGLDataType(layout->GetBufferElement()[i].dataType),
				GL_FALSE, layout->GetBufferElement()[i].stride,
				(GLvoid*)layout->GetBufferElement()[i].offset);

			index++;
		}

		glBindBuffer(GL_ARRAY_BUFFER, 0);
		glBindVertexArray(0);
	}

	void GLVertexBuffer::Bind()
	{
		glBindVertexArray(VAO);
	}

	void GLVertexBuffer::Unbind()
	{
		glBindVertexArray(0);
	}

	GLenum GetGLDataType(DataType dataType)
	{

		switch (dataType)
		{
		case DataType::Float:
		{
			return GL_FLOAT;
			break;
		}
		case DataType::Float2:
		{
			return GL_FLOAT;
			break;
		}
		case DataType::Float3:
		{
			return GL_FLOAT;
			break;
		}
		case DataType::Float4:
		{
			return GL_FLOAT;
			break;
		}
		default:
			return -1;
			break;
		}
	}

	unsigned int GetComponentCount(DataType dataType)
	{
		switch (dataType)
		{
		case DataType::Float:
		{
			return 1;
			break;
		}
		case DataType::Float2:
		{
			return 2;
			break;
		}
		case DataType::Float3:
		{
			return 3;
			break;
		}
		case DataType::Float4:
		{
			return 4;
			break;
		}
		default:
			return -1;
			break;
		}
	}

}