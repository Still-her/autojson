# autojson
json 和 c 结构体

首先感谢 rapidjson 这个库
rapidjson是腾讯的开源json解析框架，用c++实现。由于全部代码仅用header file实现，所以很容易集成到项目中。

autojson.cpp可以根据 json模板生成c结构体头文件，以及c转json串和json串转c的两个cpp，生成的cpp是基本符合rapidjson库的标准要求
可参考 rapidjson官方教程http://rapidjson.org/zh-cn/md_doc_tutorial_8zh-cn.html

此工具不做任何保证，在生成的.h .cpp 中可手动修改代码，以保证正常编译运行，从而达到适合的环境要求。

json模板数据要求,正确示范  

{
	"trafficFilters": [
	{
      "flowDescriptions": [
        {"ss":0}
      ]
    }
	],
	"id1": "1"
}

/////////////////
buglist

1.整个消息体必须以最简单的"key":"value"结尾, 尽可能的在消息体中间 ']','}' 后面加,"key":"value" 这样的字段 (原因与字符判断相关) (生成后删除对应无效字段代码)
2.可能缺括号，自行补齐

[] 里面必须含有 基本数据类型值 或者一个object值 有且只有一个
{} 里面必须有key, "key":value

错误示范1) [] 里面含有多个object

 "trafficFilters": [
	{
      "flowId": 0,
      "flowDescriptions": [
        {"ss":0}
      ]
    },
	{
      "flowId": 0,
      "flowDescriptions": [
        {"ss":0}
      ]
    }
  ],
 
 错误示范2) [] 没有具体值

 "trafficFilters": [	{      "flowId": 0,
      "flowDescriptions": [
        
      ]
    }
  ],

  
  错误示范3) object {}没有key, "key":value
  
  "trafficFilters": [
	"test":0
	{
      "flowId": 0,
      "flowDescriptions": [
        {}
      ]
    }
  ],
  
  "snssai": {
  }

  错误示范4) obj{},obj{} 中间是, 可能会core
  
  {
	"test":0
	{
      "flowId": 0,
      "flowDescriptions": [
        {}
      ]
    },  // obj{},obj{} 中间可以是,{},"":"" 是会core
	"snssai": "123"
  }
  
若需要用此APP生成结构体及基于repadjson的解析cpp文件
必须遵循以上要求

当json格式与上冲突时,可以修改json模板数据格式，满足以上要求
然后再生成的文件里面稍作修改亦可达到想要的目标文件。


目前一定还存在未知的json串不能正确解析bug，需要手动修改生成代码。
