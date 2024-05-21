#pragma once
//file_systemを互換性の観点から使いたい気持ちと使いたくない気持ちが半々。モジュールを差し替えられるようにはしておく
namespace Lib{
namespace Utility{
class IFileSystem
{
        public:
        IFileSystem(){}
        virtual ~IFileSystem(){}
        
};
}
}
