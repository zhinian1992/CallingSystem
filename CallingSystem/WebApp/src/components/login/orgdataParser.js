var allData = "{\"msg\":\"success\",\"code\":0,\"data\":[{\"name\":\"于家务社区卫生服务中心\",\"id\":1,\"list\":[{\"name\":\"口腔科\",\"id\":2,\"list\":[{\"name\":\"口腔科诊室\",\"id\":\"1\",\"list\":[{\"name\":\"口腔科诊室\",\"id\":2}]},{\"name\":\"口腔科二\",\"id\":\"9\",\"list\":[{\"name\":\"口腔科二\",\"id\":2}]}]},{\"name\":\"普通内科\",\"id\":3,\"list\":[{\"name\":\"普通内科诊室\",\"id\":\"2\",\"list\":[{\"name\":\"普通内科诊室\",\"id\":3}]}]},{\"name\":\"外科\",\"id\":4,\"list\":[{\"name\":\"外科诊室\",\"id\":\"3\",\"list\":[{\"name\":\"外科诊室\",\"id\":4}]}]},{\"name\":\"妇产科\",\"id\":5,\"list\":[{\"name\":\"妇产科诊室\",\"id\":\"4\",\"list\":[{\"name\":\"妇产科诊室\",\"id\":5}]}]},{\"name\":\"儿科\",\"id\":6,\"list\":[]},{\"name\":\"预防保健科\",\"id\":7,\"list\":[]},{\"name\":\"中医科\",\"id\":8,\"list\":[]},{\"name\":\"皮肤科\",\"id\":9,\"list\":[]},{\"name\":\"专家内科\",\"id\":10,\"list\":[]},{\"name\":\"全科医疗科\",\"id\":11,\"list\":[]},{\"name\":\"专家中医科\",\"id\":12,\"list\":[]}]},{\"name\":\"永乐店社区卫生服务中心\",\"id\":13,\"list\":[{\"name\":\"全科医疗科\",\"id\":14,\"list\":[{\"name\":\"全科医疗科诊室\",\"id\":\"5\",\"list\":[{\"name\":\"全科医疗科诊室\",\"id\":14}]}]},{\"name\":\"中医骨伤科\",\"id\":15,\"list\":[{\"name\":\"中医骨伤科诊室\",\"id\":\"6\",\"list\":[{\"name\":\"中医骨伤科诊室\",\"id\":15}]}]},{\"name\":\"中医科\",\"id\":16,\"list\":[{\"name\":\"中医科诊室\",\"id\":\"7\",\"list\":[{\"name\":\"中医科诊室\",\"id\":16}]}]}]}],\"type\":5001}";

function parseChildNode(obj){
    let node = {
        value:obj.name,
        label:obj.name,
        code:obj.id,
    };
    if(typeof(obj.list) != "undefined" && obj.list.length>0){
        node.children = [];
        for(let item of obj.list){
            node.children.push(parseChildNode(item));
        }
    }
    return node;
}

function parseOrgString2List(msg){
    if(msg == null)
        msg = allData;
    msg = JSON.parse(msg);
    let arr = [];
    for(let item of msg.data)
    {
        let node = parseChildNode(item);
        console.log(node);
        arr.push(node);
    }
    return arr;
}

export default parseOrgString2List;
