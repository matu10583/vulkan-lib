#include "Lib/Utility/File.h"
#include <assert.h>

namespace Lib {
	namespace Utility {
		bool File::ReadFile(char const* _filePath,
			bool isBin) {
			std::ifstream fin;

			fin.open(_filePath,
				std::ios::in |
				((isBin) ? std::ios::binary : 0) |
				std::ios::ate);
			if (!fin.is_open()) {
				return false;
			}
			m_size = static_cast<uint64_t>(fin.seekg(0, std::ios::end).tellg());
			fin.seekg(0, std::ios::beg);

			m_pData.reset(new uint8_t[m_size]);
			fin.read(reinterpret_cast<char*>(m_pData.get()), m_size);
			fin.close();
			return true;
		}
		void
			File::Term() {
			m_pData.reset(nullptr);
			m_size = 0;
		}

		uint8_t* File::Data() const
		{
			return m_pData.get();
		}

		bool
			File::WriteFile(char const* _filePath, size_t _size,
				uint8_t* _pData, bool isBin, bool isAdd) {
			std::ofstream ofs(_filePath,
				(std::ios::out) |
				((isBin) ? std::ios::binary : 0) |
				((isAdd) ? std::ios::app : 0)
			);
			if (!ofs.is_open()) {
				return false;
			}
			if (isBin) {
				ofs.write(reinterpret_cast<char*>(_pData), _size);
			}
			else {
				assert(false &&
					"知らねーーーーーーーーー！！文字とか軟弱なやつ書き込むな！！！！！");
			}

			if (ofs.bad()) {
				return false;
			}

			return true;
		}
	}
	
}
