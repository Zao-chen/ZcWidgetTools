# ZcWidgetTools

🎨 **基于 Qt 的现代化控件库 - ElaWidgetTools 的最佳伴侣** 🎨

[![GitHub Release](https://img.shields.io/github/v/release/Zao-chen/ZcWidgetTools?include_prereleases&style=for-the-badge)](https://github.com/Zao-chen/ZcWidgetTools/releases)
[![GitHub License](https://img.shields.io/github/license/Zao-chen/ZcWidgetTools?style=for-the-badge)](LICENSE)
[![GitHub commit activity](https://img.shields.io/github/commit-activity/m/Zao-chen/ZcWidgetTools?style=for-the-badge)](https://github.com/Zao-chen/ZcWidgetTools/commits)
[![GitHub Downloads (all assets, all releases)](https://img.shields.io/github/downloads/Zao-chen/ZcWidgetTools/total?style=for-the-badge)](https://github.com/Zao-chen/ZcWidgetTools/releases)
[![GitHub Repo stars](https://img.shields.io/github/stars/Zao-chen/ZcWidgetTools?style=for-the-badge)](https://github.com/Zao-chen/ZcWidgetTools/stargazers)
[![GitHub Issues or Pull Requests](https://img.shields.io/github/issues/Zao-chen/ZcWidgetTools?style=for-the-badge)](https://github.com/Zao-chen/ZcWidgetTools/issues)

### [English](/README.md) 中文

---

## 🎯 项目介绍

ZcWidgetTools 是为 [ElaWidgetTools](https://github.com/Liniyous/ElaWidgetTools) 打造的补充控件库。

ElaWidgetTools 提供了完整的 Fluent UI 组件库，而 **ZcWidgetTools** 专注于补充那些尚未实现的控件和高级动画效果。两者配合使用，助你打造极致的现代化应用！

---

## 🎗️补充的控件

| 目录              | 说明   | 备注                        |
| --------------- | ---- | ------------------------- |
| ZcStackedWidget | 堆叠窗口 | 类似于Win11设置中的子菜单效果，有左右划入划出 |

## 🚀 快速入门

### 📋 Step 1 - 下载库文件

1. 在 [Release 页面](https://github.com/Zao-chen/ZcWidgetTools/releases) 下载最新版本。
2. 解压后得到lib和include文件夹。

### 📁 Step 2 - 集成到你的项目

将两个文件夹复制到你的项目，如果你使用了 ElaWidgetTools 或者是已经有这两个文件夹了，请进行合并。

### ⚙️ Step 3 - 配置 CMakeLists.txt

在你的 `CMakeLists.txt` 中添加以下内容：

```cmake
# 添加头文件路径
target_include_directories(YourProject PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}/include
)

# 链接库文件
target_link_libraries(YourProject PRIVATE
    Qt6::Widgets
    ${CMAKE_CURRENT_SOURCE_DIR}/lib/ZcWidgetTools.lib
)

# 自动复制 DLL 到可执行文件目录
add_custom_command(TARGET YourProject POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_if_different
    "${CMAKE_CURRENT_SOURCE_DIR}/lib/ZcWidgetTools.dll"
    $<TARGET_FILE_DIR:YourProject>
    COMMENT "Copying ZcWidgetTools.dll"
)
```

### 💻 Step 4 - 开始使用

在你的代码中引入并使用：

将stackedWidget提升到ZcstackedWidget，

并使用

```c++
stack->slideToIndex(index);
```

来替代

```c++
stack->setCurrentIndex(index)
```

---

## ❓ 常见问题 (F&Q)

### 🤔 为什么不直接提交到 ElaWidgetTools？

ElaWidgetTools 不接受任何 PR，所以只好单独开了 ZcWidgetTools。

---

## 🤗 如何贡献

ZcWidgetTools 是一个开源项目。参与项目的方法有很多！

- **为项目做出贡献**：有兴趣做出贡献吗？欢迎 [Pull Request](https://github.com/Zao-chen/ZcWidgetTools/pulls)！
- **报告 BUG、建议**：发现问题或有功能请求？请通过 [Issues](https://github.com/Zao-chen/ZcWidgetTools/issues) 提交。
- **或者……**：给项目来一个 star⭐ 怎么样？

---

## 🔗 相关链接

- [Liniyous/ElaWidgetTools: Fluent-UI For QT-Widget](https://github.com/Liniyous/ElaWidgetTools)
