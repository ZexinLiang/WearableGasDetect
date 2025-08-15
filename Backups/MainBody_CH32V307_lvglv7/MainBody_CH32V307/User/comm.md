# 通信协议
## m780eg
### 上报数据
**上报气体信息：** head(2B)+gas1(4B)+gas2(4B)+gas3(4B)+tail(2B)
### 下行数据
**GPS地址获取：** head(2B)+lo(10B)+la(10B)+tail(2B)
**气体分析结果（具体浓度值）：** head(2B)+gas1(4B)+gas2(4B)+gas3(4B)+tail(2B)
**气体分析结果（分析安全值）：** head(2B)+sceneCode(3B)+tail(2B)
