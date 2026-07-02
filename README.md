# Lyrics Tray Icon Fix

这是一个为个人用途编写的 Windows 小工具，用于隐藏 BetterLyrics 和 Lyricify Lite 在托盘中错误多出来的 `H.NotifyIcon_*` 图标。

当前确认可用版本：`v0.20-target-self-delete-hnotify`。

## 用途

本项目不是通用托盘管理器，也不是 PS Tray Factory 的替代品。它只用于补足 PS Tray Factory 对 BetterLyrics / Lyricify Lite 错误托盘图标隐藏不稳定的问题。

## 使用

从本仓库下载 `lyrics-tray-icon-fix-v0.20.zip`，解压后双击：

```text
Install and start v0.20.cmd
```

停止并移除开机启动：

```text
Stop and disable v0.20.cmd
```

## 实现

v0.20 使用 Windows 消息 Hook，不是持续轮询。它不主动刷新 PS Tray Factory 的托盘列表，避免冲掉 PS Tray Factory 中自定义的托盘图标图片。

## 许可

MIT License。
