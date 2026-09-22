# 算法作业

这个仓库用于保存算法作业及其版本记录。

## 文件结构

- `homework/linked_list_max/my_version.cpp`：自己编写的最新版本。
- `homework/linked_list_max/reference_version.cpp`：可运行的参考版本。
- `homework/linked_list_max/drafts/my_original_draft.cpp`：最初误存为 `.py` 的草稿，原样保留。
- `archive/empty_files/算法`：之前创建的空文件，仅归档，不作为代码运行。
- `.vscode/`：VS Code 的 C++ 一键编译和运行配置。
- `.venv/`：原有 Python 虚拟环境，不是算法源代码。

## 运行 C++ 文件

在 VS Code 中打开需要运行的 `.cpp` 文件，然后点击编辑器右上角的运行按钮。程序会自动编译到英文临时目录，避免中文路径导致的 GCC 错误。
