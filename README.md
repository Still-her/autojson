# autojson
json 和 c 结构体

首先感谢 rapidjson 这个库
rapidjson是腾讯的开源json解析框架，用c++实现。由于全部代码仅用header file实现，所以很容易集成到项目中。

autojson.cpp可以根据 json模板生成c结构体头文件，以及c转json串和json串转c的两个cpp，生成的cpp是基本符合rapidjson库的标准要求
可参考 rapidjson官方教程http://rapidjson.org/zh-cn/md_doc_tutorial_8zh-cn.html


当json格式与上冲突时,可以修改json模板数据格式，满足以上要求
然后再生成的文件里面稍作修改亦可达到想要的目标文件。
