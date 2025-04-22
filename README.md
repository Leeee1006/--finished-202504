# 📦 快递驿站管理系统（C语言 + EasyX 图形界面）

本项目为一个基于 **C语言** 与 **EasyX 图形库** 实现的轻量级快递驿站管理平台，支持用户、系统管理员和驿站运营员三种角色，覆盖从包裹寄取、库存管理到运营数据分析的核心流程，旨在打造**稳定、高效、易用**的交互式校园物流管理系统。

---

## 🧠 系统概述

该系统通过模块化设计与结构化数据存储，实现了以下功能：

- **用户注册登录**、包裹管理、优惠券使用等自助服务
- **管理员端智能库存**、用户管理、数据分析、工单处理
- **运营员端包裹入库**、寄件/取件提醒、送件/上门服务等流程支持

> 图形化界面基于 EasyX 实现，所有模块均支持交互操作与错误提示。

---

## 📐 开发规范

| 规范项 | 内容 |
|--------|------|
| 命名方式 | 驼峰命名法 |
| 代码风格 | Allman 风格大括号换行 |
| 编译环境 | Visual Studio 2022 |
| 操作系统 | Windows 11 |
| 字符编码 | GBK（适配中文） |
| 金额单位 | 精确到元、角、分 |

---

## 🧾 数据结构约定（common.h）

### 🔹 用户相关结构体

| 属性 | 类型 |
|------|------|
| experience | unsigned int |
| couponCount | unsigned short |
| discount | unsigned short |
| userType | UserType |
| userName | char[NAME] |
| phoneNumber | char[PHONE] |
| identityCode | char[ID_CODE] |
| password | char[PASSWORD] |

### 🔹 包裹信息结构体

| 属性 | 类型 |
|------|------|
| volume, weight, shippingFee | float |
| packageType | PackageType |
| shippingMethod | ShippingMethod |
| packageState | PackageState |
| usedCouponNum | unsigned short |
| isHomeDelivered / isHomeSent | bool |
| trackingNum, pickupCode, packageName | char[] |
| sender/receiverPhone/Address, dormAddress | char[] |
| time（结构体） | PackageTime（含 ordered/shipped 等）|

### 🔹 货架与运营数据

| 属性 | 类型 |
|------|------|
| volumeCapacity / occupiedVolume | float |
| packageNum | int |
| weeklyRevenue | double |
| sendCount / pickupCount / remainPackages | int |

### 🔹 工单与日志

| 属性 | 类型 |
|------|------|
| ticketId | int |
| createdTime | time_t |
| ticketType | TicketType |
| description | char[DESCR] |
| phoneNumber | char[PHONE] |
| isHandled | bool |
| log.description / createdTime | 日志记录项 |

---

## 🔧 功能模块说明

### 👤 用户模块

1. **注册与登录**  
   - 用户通过手机号和密码完成注册和登录
   - 系统校验手机号唯一性，防止重复注册
   - 登录校验密码准确性

2. **包裹信息浏览**  
   - 用户可查看所有与其相关的包裹状态
   - 包含“待寄出”、“待取件”、“已签收”、“拒收”等多种状态

3. **我要寄件**  
   - 填写寄件人与收件人信息、地址、物品重量与体积等
   - 系统自动计算运费并生成寄件记录

4. **我要取件**  
   - 用户跳转至“待取件”界面，查看并领取包裹

5. **个人中心**  
   - 包含身份码查看、优惠券使用、会员等级、退出登录、提交工单等功能
   - 工单支持：误取、投诉建议、包裹损坏/丢失申报

---

### 🛡️ 系统管理员模块

1. **智能库存管理**  
   - 提供库存实时看板
   - 超过80%容量时红字预警
   - 支持按快递单号追踪包裹

2. **用户信息管理**  
   - 支持手机号或姓名快速搜索
   - 可对用户进行新增、修改、删除操作

3. **数据分析**  
   - 每周生成运营简报（寄件量、滞留件等）
   - 可视化预测未来14天包裹流量

4. **工单处理**  
   - 分类处理用户误取、损坏/丢失等工单
   - 实时反馈处理结果

---

### 📮 驿站运营员模块

1. **包裹入库**  
   - 录入收件人信息、地址、快递单号
   - 系统生成唯一取件码，更新状态为“待取件”

2. **送件到楼**  
   - 查看用户“送件到楼”请求
   - 确认送达后更新状态为“已取件”

3. **上门取件**  
   - 用户发起请求，运营员确认并更新状态为“已取件”

4. **通知提醒机制**  
   - 设置超时阈值（如48小时未取）
   - 系统筛选超时包裹并提醒运营员

5. **包裹寄件协助**  
   - 协助用户完成寄件流程
   - 自动记录并归档寄件记录

---

## 🧪 示例模块（截图略）

> EasyX 图形化界面支持：按钮交互、弹窗提示、输入框校验、信息提示、状态颜色标识等。

---

## 💻 编译说明

- 请使用 Visual Studio 2022 打开项目 `.sln` 文件
- 配置 EasyX 图形库（可参考 [EasyX 官网](https://easyx.cn)）
- 编译环境需支持 GBK 编码（确保中文显示正常）

---

## 🧩 技术亮点

- 🧠 自定义链表结构 + 内存池机制（模拟 STL）
- 🧊 模块化设计 + 清晰角色分层
- 📊 图形化界面 + 简洁数据可视化
- 📬 角色行为驱动式状态切换 + 完整日志体系

---

## 🙋‍♂️ 作者团队

- 负责人：李暄（登录模块 & 运营员模块）
- 组员：佘嘉雄、赵传浩、孟海波
- 项目定位：**大一课程设计，面向实战与展示**

---

## 📜 License

MIT License. Free to use, share, and modify.

---

> 如需使用、展示或改进本项目，欢迎提交 Pull Request 或 Issues 🙌
