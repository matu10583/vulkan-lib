<#
.SYNOPSIS
クラス作成ヘルパーです。
名前空間の指定と、それに合わせたディレクトリ構造の作製をします。
.PARAMETER TargetClass
作製クラス名。.区切りで名前空間を指定します。（例:A.B.C.D）
.PARAMETER src
ソースファイルディレクトリ。同階層のmake_class.confのSRC_PATHで指定している場合は省略可能
.PARAMETER inc
ソースファイルディレクトリ。同階層のmake_class.confのINC_PATHで指定している場合は省略可能
.PARAMETER extends
基底クラスの指定。名前空間付きで.区切りで指定します。
名前空間通りのパスでincludeもするがファイル名-neクラス名の時は間違えちゃうかも♪
.PARAMETER inline
指定するとcppを生成しない
<CommonParameters>はサポートしないんだからねっ！
#>
Param(
    [string]$TargetClass,
    [string]$src,
    [string]$inc,
    [switch]$inline,
    [array]$extends=@()
)

function AddNameSpace([ref]$result, [array]$name_spaces, [int]$index, [string]$Content){
    if($index -ge $name_spaces.Length){
        $result.Value += $Content
        return
    }
    $result.Value += ("namespace " + $name_spaces[$index] + "{`n")
    $next_idx = $index + 1
    AddNameSpace $result $name_spaces $next_idx $Content
    $result.Value += "}`n"

}

$CONF_FILE_PATH = "./make_class.conf"
if(Test-Path -Path $CONF_FILE_PATH){
$CONFIG=@{}
Get-Content $CONF_FILE_PATH | %{$CONFIG += ConvertFrom-StringData -StringData $_}
if($src -eq ""){
    $src = $CONFIG.SRC_PATH
}
if($inc -eq ""){
    $inc = $CONFIG.INC_PATH
}
}

$TargetClassSplit = $TargetClass.Split(".")
$TargetClassName = $TargetClassSplit[-1]
$TargetNamespaces = $TargetClassSplit[0..($TargetClassSplit.Length-2)]

$IncPath = $inc
$SrcPath = $src
$IncludePathInSrc = ""
$TargetNSCount = $TargetNamespaces.Length
for($i = 0; $i -lt $TargetNSCount; $i++){
    $ns = $TargetNamespaces[$i]
    $IncPath = Join-Path -Path $IncPath -ChildPath $ns
    
    $SrcPath = Join-Path -Path $SrcPath -ChildPath $ns
    $IncludePathInSrc += $ns + "/"
}
$IncludePathInSrc += $TargetClassName + ".h"
    if(-not (Test-Path -Path $IncPath)){
        New-Item -Path $IncPath -ItemType "directory"
    }
    if(-not (Test-Path -Path $SrcPath)){
        New-Item -Path $SrcPath -ItemType "directory"
    }
$IncPath = (Join-Path -Path $IncPath -ChildPath $TargetClassName)+".h"
$SrcPath = (Join-Path -Path $SrcPath -ChildPath $TargetClassName)+".cpp"

$ClassString = "class " + $TargetClassName +"`n"
# 継承する場合はこちらに記入
if($extends.Length -ne 0){
    $ClassString += (": ")
    foreach($ext in $extends){
        $ClassString += ("public " + $ext.Replace(".", "::"))
        if($ext -ne $extends[-1]){
            $ClassString += ",`n"
        }
        else{
            $ClassString += "`n"
        }
    }
}
$ClassString += "{"
$ClassString += "`n"
$ClassString += "};`n"

$NS_Class = ""
AddNameSpace ([ref]$NS_Class) $TargetNamespaces 0 $ClassString
$IncludeStr = "#pragma once`n"
if($extends.Length -ne 0){
    foreach($ext in $extends){
        $IncludeStr += ("#include `"" + $ext.Replace(".", "/") + ".h`"`n")
    }
}
$IncludeStr += $NS_Class
Set-Content -Path $IncPath -Value $IncludeStr

if(-not $inline){
$SrcStr = "#include `"" + $IncludePathInSrc + "`""
$NameSpaceScope = ""
AddNameSpace ([ref]$NameSpaceScope) $TargetNamespaces 0 "`n"
Set-Content -Path $SrcPath -Value $SrcStr
}
