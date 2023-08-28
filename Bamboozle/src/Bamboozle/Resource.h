#pragma once

#include <cstddef>

namespace bbzl
{
	class Resource
	{
	public:
		virtual ~Resource() = default;

		void AddRef()
		{
			++m_refCount;
		}

		bool ReleaseRef()
		{
			if (--m_refCount)
			{
				delete this;
				return false;
			}

			return true;
		}

		uint32_t getHashId() const
		{
			return m_hashId;
		}

	protected:
		Resource() = delete;
		Resource(uint32_t hashId)
			: m_hashId(hashId)
		{
		}

	private:
		size_t m_refCount = 0;
		uint32_t m_hashId;
	};

} // namespace bbzl
