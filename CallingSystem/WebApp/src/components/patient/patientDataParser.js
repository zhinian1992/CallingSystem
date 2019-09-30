let test = "{\"data\":{\"code\":0,\"msg\":\"登录成功！\",\"result\":{\"delFlag\":\"0\",\"deptCode\":\"8562\",\"id\":1,\"loginName\":\"010803\",\"ranks\":\"主治医师\",\"ranksLevel\":\"40\",\"remarks\":[{\"age\":\"1\",\"aheadNum\":0,\"appointPeriod\":\"1\",\"appointTime\":1568857850000,\"cardNo\":\"1\",\"counterId\":1,\"counterName\":\"口腔科诊室\",\"createTime\":1568856364000,\"deptCode\":\"8562\",\"deptId\":2,\"deptName\":\"口腔科\",\"encryptionPatientName\":\"张*\",\"endTime\":1568888411000,\"hosid\":\"1219\",\"id\":2149,\"isDistribution\":\"1\",\"isPrior\":\"0\",\"patientId\":3411,\"patientName\":\"张三\",\"patientType\":\"0\",\"ranksLevel\":\"40\",\"registerNo\":\"SD1568856363677\",\"reportTime\":1569376250000,\"serviceId\":1,\"serviceName\":\"口腔科诊室\",\"sort\":1,\"staffLoginId\":\"010803\",\"staffName\":\"葛玉菊\",\"startTime\":1568888409000,\"status\":\"1\",\"ticketNo\":\"001\",\"type\":\"0\"},{\"age\":\"1\",\"aheadNum\":0,\"appointPeriod\":\"1\",\"appointTime\":1568857999000,\"cardNo\":\"1\",\"counterId\":1,\"counterName\":\"口腔科诊室\",\"createTime\":1568856792000,\"deptCode\":\"8562\",\"deptId\":2,\"deptName\":\"口腔科\",\"encryptionPatientName\":\"李*\",\"endTime\":1568888413000,\"hosid\":\"1219\",\"id\":2150,\"isDistribution\":\"1\",\"isPrior\":\"0\",\"patientId\":3412,\"patientName\":\"李四\",\"patientType\":\"0\",\"ranksLevel\":\"40\",\"registerNo\":\"SD1568856792271\",\"reportTime\":1569376250000,\"serviceId\":1,\"serviceName\":\"口腔科诊室\",\"sort\":2,\"staffLoginId\":\"010803\",\"staffName\":\"葛玉菊\",\"startTime\":1568888411000,\"status\":\"1\",\"ticketNo\":\"002\",\"type\":\"0\"}],\"staffName\":\"葛玉菊\"},\"success\":true},\"type\":2}";

let states = {
    "waitCalling":1,
    "onCalling":2,
    "skipCalling":4,
    "doneCalling":5
}

function parsePatientString2Object(msg){
    // if(msg == null)
    //     msg = test;
    let currentList = [];
    let skipList = [];
    let doneList = [];
    let data = JSON.parse(msg).data.result;

    let doctorName = data.staffName;

    for(let patient of data.remarks){
        let record = {
            "key":patient.id,
            "id":patient.sort,
            "name":patient.patientName,
            "status":"",
        }
        if(patient.status == states.waitCalling){
            record.status = "候诊";
            currentList.push(record);
        }
        else if(patient.status == states.onCalling){
            record.status = "正在呼叫";
            currentList.push(record);
        }
        else if(patient.status == states.skipCalling){
            record.status = "过号";
            skipList.push(record);
        }
        
        else if(patient.status == states.doneCalling){
            record.status = "已就诊";
            doneList.push(record);
        }
    }

    let obj = {
        current:currentList,
        skip:skipList,
        done:doneList,
        doctor:doctorName
    }
    return obj;
}

export default parsePatientString2Object;