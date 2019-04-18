#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<cJSON.h>

int test0()
{
    char *json_string ="{\"test_1\":\"fengxin\",\"test_2\":\"123\",\"test_3\":\"1\"}";
    /* "{\ */
    /*  "test_1\":\"0\",\ */
    /*  "test_2\":\"1\",\ */
    /*  "test_3\":\"2\" */
    /* }"; */

    cJSON *pcjson = cJSON_Parse(json_string); //JSON字符串到cJSON格式
    
    if(pcjson == NULL)
    {
        printf("json pack into cjson error.");
    }
    else
    {
        cJSON_Print(pcjson); // 打包
    }

    char *test_1_string = cJSON_GetObjectItem(pcjson, "test_1")->valuestring;
    char *test_2_string = cJSON_GetObjectItem(pcjson, "test_2")->valuestring;
    char *test_3_string = cJSON_GetObjectItem(pcjson, "test_3")->valuestring;

    printf("%s", test_1_string);
    printf("%s", test_2_string);
    printf("%s", test_3_string);

    cJSON_Delete(pcjson);
    return 0;
}

int test1()//创建一个对象
{
    cJSON *usr;
    cJSON *arry;

    usr = cJSON_CreateObject(); //创建根数据对象
    cJSON_AddStringToObject(usr, "name", "fengxin"); //加入键值，加字符串
    cJSON_AddStringToObject(usr, "passwd", "123"); 
    cJSON_AddNumberToObject(usr, "num", 1);

    char *out = cJSON_Print(usr);
    printf("%s\n", out);

    cJSON_Delete(usr);
    free(out);
    return 0;
}

int test2()  //创建一个数组
{
    cJSON *root, *js_body;
    root = cJSON_CreateArray();
    cJSON_AddItemToArray(root, cJSON_CreateString("Hello world"));
    cJSON_AddItemToArray(root, cJSON_CreateNumber(10));
    {
        char *s = cJSON_PrintUnformatted(root);
        if(s)
        {
            printf(" %s \n", s);
            free(s);
        }
    }
    if(root)
    { cJSON_Delete(root); }

    return 0;
}

int test3()
{
    cJSON *root, *js_body, *js_list, *js_list2;
    root = cJSON_CreateObject();
    
    cJSON_AddItemToObject(root, "body", js_body = cJSON_CreateArray());

    cJSON_AddItemToArray(js_body, js_list = cJSON_CreateObject());
    cJSON_AddStringToObject(js_list, "name", "fengxin");
    cJSON_AddNumberToObject(js_list, "status", 100);
    
    cJSON_AddItemToArray(js_body, js_list2 = cJSON_CreateObject());
    cJSON_AddStringToObject(js_list2, "name", "venne");
    cJSON_AddNumberToObject(js_list2, "status", 200);
    {
        //char *s = cJSON_PrintUnformatted(root);
        char *s = cJSON_Print(root);
        if(s)
        {
            printf(" %s \n", s);
            free(s);
        }
    }
    if(root)
    { cJSON_Delete(root); }
    
    return 0;
}

int test4() //解析json (单层)
{
    cJSON *json, *json_name, *json_passwd, *json_num;
    char *out = "{\"name\":\"fengxin\",\"passwd\":\"123\",\"num\":1}";

    json = cJSON_Parse(out);
    json_name = cJSON_GetObjectItem(json, "name");
    json_passwd = cJSON_GetObjectItem(json, "passwd");
    json_num = cJSON_GetObjectItem(json, "num");

    printf("name:%s\npasswd:%s\nnum:%d\n", json_name->valuestring, json_passwd->valuestring, json_num->valueint);

    cJSON_Delete(json);
    return 0;
}

int test5() //解析 有父层
{
    char *s = "{\"list\":{\"name\":\"xiao hong\",\"age\":10},\"other\":{\"name\":\"hua hua\"}}";
    cJSON *root = cJSON_Parse(s);
    if(!root)
    { printf("get root failed\n"); return -1; }

    cJSON *js_list = cJSON_GetObjectItem(root, "list");
    if(!js_list)
    { printf("no list\n"); return -1; }
    printf("list type is %d\n", js_list->type);

    cJSON *name = cJSON_GetObjectItem(js_list, "name");
    if(!name)
    { printf("no name\n"); return -1; }
    printf("name type is %d\n", name->type);
    printf("name: %s\n", name->valuestring);

    cJSON *age = cJSON_GetObjectItem(js_list, "age");
    if(!age)
    { printf("no age\n"); return -1; }
    printf("age type is %d\n", age->type);
    printf("age : %d\n", age->valueint);

    cJSON *js_other = cJSON_GetObjectItem(root, "other");
    if(!js_other)
    { printf("no list\n"); return -1; }
    printf("list type is %d\n", js_other->type);

    cJSON *other_name = cJSON_GetObjectItem(js_other, "name");
    if(!other_name)
    { printf("no name\n"); return -1; }
    printf("name type is %d\n", other_name->type);
    printf("name:%s\n", other_name->valuestring);

    if(root)
        cJSON_Delete(root);
    return 0;
    
}

int test6() // 解析 数组
{
    char *s = "{\"list\":[\"name1\",\"name2\"]}";
    cJSON *root = cJSON_Parse(s);
    if(!root)
    { printf("get root failed\n"); return -1; }
    
    cJSON *js_list = cJSON_GetObjectItem(root, "list"); //先获取list
    if(!js_list)
    { printf("no list\n"); return -1; }
    int array_size = cJSON_GetArraySize(js_list);   //获取数组成员个数
    printf("arr size is %d\n", array_size);

    cJSON *item;
    for(int i = 0; i < array_size; ++i)         //依次获取
    {
        item = cJSON_GetArrayItem(js_list, i);
        printf("item type is %d\n", item->type);
        printf("%s\n", item->valuestring);
    }

    if(root)
    { cJSON_Delete(root); }
    return 0;
}


int main()
{
    //test0();
    //test1();
    //test2();
    //test3();
    //test4();
    //test5();
    test6();
    return 0;
}
