#pragma once
#include <filesystem>
#include <fstream>
#include <memory>

namespace Lib {
	namespace Utility {
		class File
		{
		public:
			File()
				:m_pData(nullptr)
				, m_size(0)
			{}
			~File() {
				Term();
			}

			bool ReadFile(char const* _filePath, bool isBin = true);
			void Term();

			uint8_t* Data()const;
			auto GetSize() const {
				return m_size;
			}

			static bool WriteFile(char const* _filePath, size_t _size,
				uint8_t* _pData, bool isBin = true, bool isAdd = false);

		private:
			uint64_t m_size;
			std::unique_ptr<uint8_t[]> m_pData;
		};
	}
}



