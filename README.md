# autojson
json 和 c 结构体

首先感谢 rapidjson 这个库
rapidjson是腾讯的开源json解析框架，用c++实现。由于全部代码仅用header file实现，所以很容易集成到项目中。

autojson.cpp可以根据 json模板生成c结构体头文件，以及c转json串和json串转c的两个cpp，生成的cpp是基本符合rapidjson库的标准要求
可参考 rapidjson官方教程http://rapidjson.org/zh-cn/md_doc_tutorial_8zh-cn.html
在生成的文件里面稍作修改即可达到想要的目标文件。

在data_json串里面数组只能包含一种Object。如，key:[{}], 错误如 key:[{},{}]

例子：
1.在 data_json文件里面保存json模板串
2.编译：g++ autojson2.cpp -o autojson
3.运行 autojson data_json
4.生成目标文件
