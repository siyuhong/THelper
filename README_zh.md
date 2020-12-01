# THelper

[英文页](README.md) |

![GitHub](https://img.shields.io/github/license/RT-Thread/rt-thread.svg)


一个简单的 ``Qt`` 工程 - 翻译工具

# 开发环境
- Qt 5.9.3
- Windows 7_64

# 已接入的API
- [百度翻译API](https://api.fanyi.baidu.com/doc/21)
- [腾讯AI开发平台 - 文本翻译](https://ai.qq.com/doc/nlptrans.shtml)

目前均为免费，如有其他免费的API，欢迎告知。  ~择时加上~

# 如何使用
- 如果你打算直接编译，请下载源码并到所使用的API平台上注册，取得 ``KEY`` 和 ``APPID``。
- 打开文件 ``BaiduTranslate.h`` & ``TencentTranslateAPI.h``，修改``KEY`` 和 ``APPID``。
- 编译生成可执行文件（``qmake`` 不可或缺）。
- 如果你只是单纯的需要使用这个工具，直接下载可执行文件即可，目前仅有 ``Windows_64`` 版本，如需其他系统版本，可告知~

# 展示
- 版本 V0.1

  ![image](https://github.com/siyuhong/THelper/blob/master/show/demov0.1.png)

- 版本 V0.2

  ![image](https://github.com/siyuhong/THelper/blob/master/show/demov0.2.png)
#
