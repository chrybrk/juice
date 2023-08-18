#pragma once

#include "core/utils.hpp"
#include "shader/shader.hpp"

namespace juice {

	//////////////////////////////////////
	//			Buffer Layout			//
	//////////////////////////////////////

	class BufferLayout
	{
        public:

            BufferLayout() {}

            BufferLayout(const std::initializer_list<BufferElement>& elements)
                : m_Elements(elements)
            {
                CalcOffsetandStride();
            }

            inline const std::vector<BufferElement>& GetElements() const { return m_Elements; }

            inline const std::uint32_t GetStride() const { return m_Stride; }

            std::vector<BufferElement>::iterator begin() { return m_Elements.begin(); }
            std::vector<BufferElement>::iterator end() { return m_Elements.end(); }
            
            std::vector<BufferElement>::const_iterator begin() const { return m_Elements.begin(); }
            std::vector<BufferElement>::const_iterator end() const { return m_Elements.end(); }

        private:
            void CalcOffsetandStride()
            {
                std::uint32_t offset = 0;
                m_Stride = 0;
                for (auto& element : m_Elements)
                {
                    element.Offset = offset;
                    offset += element.Size;
                    m_Stride += element.Size;
                }
            }
        private:
            std::vector<BufferElement> m_Elements;
            std::uint32_t m_Stride = 0;
	};

	//////////////////////////////////////
	//			Vertex Buffer			//
	//////////////////////////////////////

	class VertexBuffer
	{
        public:
            VertexBuffer(float* data, std::uint32_t size);
            ~VertexBuffer() {};

            void Bind() const;
            void Unbind() const;

            void SetLayout(const BufferLayout& layout) { m_Layout = layout; };
            inline const BufferLayout& GetLayout() const { return m_Layout; };

        private:
            std::uint32_t m_VertexBufferID;
            std::uint32_t m_Size;
            BufferLayout m_Layout;
	};

	//////////////////////////////////////
	//			Index Buffer			//
	//////////////////////////////////////

	class IndexBuffer
	{
        public:
            IndexBuffer(unsigned short int* data, std::uint32_t count);
            IndexBuffer(std::uint32_t* data, std::uint32_t count);
            ~IndexBuffer();

            void Bind() const;
            void Unbind() const;

            inline std::uint32_t GetCount() const { return m_Count; }

        private:
            std::uint32_t m_BufferID;
            std::uint32_t m_Count;
	};

	//////////////////////////////////////
	//			Vertex Array			//
	//////////////////////////////////////

	class VertexArray
	{
        public:
            VertexArray();
            ~VertexArray() {};

            void Bind() const;
            void Unbind() const;

            void AddVertexBuffer(const ref<VertexBuffer>& vertexBuffer);
            void SetIndexBuffer(const ref<IndexBuffer>& indexBuffer);

            const std::vector<ref<VertexBuffer>> GetVertexBuffers() const { return m_VertexBuffers; }
            const ref<IndexBuffer> GetIndexBuffer() const { return m_IndexBuffer; }

        private:
            uint32_t m_VertexArrayID;
            std::vector<ref<VertexBuffer>> m_VertexBuffers;
            ref<IndexBuffer> m_IndexBuffer;
	};

}
