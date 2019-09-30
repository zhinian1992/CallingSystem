import React from 'react';
import { Tabs, Table, Divider } from 'antd';
import "antd/dist/antd.css";
import styled, { createGlobalStyle } from "styled-components";
import parsePatientString2Object from './patientDataParser';
import OperationTipForm from './callingView';
import ErrorTipForm from '../error/errorView'

const { TabPane } = Tabs;


export default class PatientView extends React.Component{
    constructor(props){
        super(props);

        this.columns = [
        {
            title: '编号',
            dataIndex: 'id',
            key: 'id',
            width:'10%',
        },
        {
            title: '姓名',
            dataIndex: 'name',
            key: 'name',
            width:'20%',
        },
        {
          title: '状态',
          dataIndex: 'status',
          key: 'status',
          width:'20',
        },
        {
            title: '操作',
            dataIndex: 'operation',
            key: 'operation',
            width:"50",
            render: (text, record) => 
              (
                <span>
                  <a onClick={() => this.handleCallingRequest(record.key)}>呼叫</a>
                  <Divider type="vertical" />
                  <a onClick={() => this.handleSkipRequest(record.key)}>过号</a>
                  <Divider type="vertical" />
                  <a onClick={() => this.handleTreatedRequest(record.key)}>已就诊</a>
                </span>
              ),
          },
        ];

        this.columns_done = [
          {
              title: '编号',
              dataIndex: 'id',
              key: 'id',
              width:'10%',
          },
          {
              title: '姓名',
              dataIndex: 'name',
              key: 'name',
              width:'20%',
          }
        ];

        let patientObj = parsePatientString2Object(window.localStorage.getItem("patientString"));
        this.state ={
          currentList:patientObj.current,
          skipList:patientObj.skip,
          doneList:patientObj.done,
          doctor:patientObj.doctor,
          tabIndex:"current",
        }

        this.changeTab = this.changeTab.bind(this);

        //回调方法
        window.callingSucceed = (params) => this.callingSucceed(params);
        window.callingFailed = (params) => this.callingFailed(params);
        window.skipPatientSucceed = (params) => this.skipPatientSucceed(params);
        window.skipPatientFailed = (params) => this.skipPatientFailed(params);
        window.treatedSucceed = (params) => this.treatedSucceed(params);
        window.treatedFailed = (params) => this.treatedFailed(params);
        window.refreshPrompt = (params) => this.refreshPrompt(params);
        window.getQueueSucceed = (params) => this.getQueueSucceed(params);
        window.getQueueFailed = (params) => this.getQueueFailed(params);
        window.connectionFailed = (params) => this.connectionFailed(params);
        window.connectionSucceed = (params) => this.connectionSucceed(params);
        window.remoteLogin = (params) => this.remoteLogin(params);
    }

    componentDidMount(){
      if(window.RegisterCallback){
          // 注册呼叫成功回调
          window.RegisterCallback(JSON.stringify({type:7001,method:"callingSucceed"}));
          // 注册呼叫失败回调
          window.RegisterCallback(JSON.stringify({type:7002,method:"callingFailed"}));
          // 注册过号成功回调
          window.RegisterCallback(JSON.stringify({type:7101,method:"skipPatientSucceed"}));
          // 注册过号失败回调
          window.RegisterCallback(JSON.stringify({type:7102,method:"skipPatientFailed"}));
          // 注册完成诊疗成功回调
          window.RegisterCallback(JSON.stringify({type:7201,method:"treatedSucceed"}));
          // 注册完成诊疗失败回调
          window.RegisterCallback(JSON.stringify({type:7202,method:"treatedFailed"}));
          // 注册服务端提示刷新回调
          window.RegisterCallback(JSON.stringify({type:8000,method:"refreshPrompt"}));
          // 注册获取队列成功回调
          window.RegisterCallback(JSON.stringify({type:8001,method:"getQueueSucceed"}));
          // 注册获取队列失败回调
          window.RegisterCallback(JSON.stringify({type:8002,method:"getQueueFailed"}));
          // 注册服务端推送患者回调
          window.RegisterCallback(JSON.stringify({type:8100,method:"addPatientToQueue"}));
          // 注册网络异常回调
          window.RegisterCallback(JSON.stringify({type:1002,method:"connectionFailed"}));
          // 注册异地登录回调
          window.RegisterCallback(JSON.stringify({type:6003,method:"remoteLogin"}));
      }
    }

    remoteLogin = msg => {
      console.log("remoteLogin");
      ErrorTipForm.showTipForm();
    };

    connectionFailed = msg => {
      console.log("connectionFailed");
      this.props.history.push('/init');
    };
    
    callingSucceed = msg => {
      console.log("callingSucceed");
      OperationTipForm.showTipForm({
        content:'呼叫成功!',
      });

      let id = JSON.parse(msg).id;

      console.log(this.state.tabIndex);
      if(this.state.tabIndex == "current"){
        for(let item in this.state.currentList){
          if(this.state.currentList[item].key == id){
            this.state.currentList[item].status = "正在呼叫";
            console.log(this.state.currentList);
            const dataSource = this.state.currentList;
            this.setState({currentList:dataSource});
          }
        }
      }
      else if(this.state.tabIndex == "skip"){
        for(let item in this.state.skipList){
          if(this.state.skipList[item].key == id){
            this.state.skipList[item].status = "正在呼叫";
            console.log(this.state.skipList);
            const dataSource = this.state.skipList;
            this.setState({skipList:dataSource});
          }
        }
      }
    };

    callingFailed = msg => {
      console.log("callingFailed");

      OperationTipForm.showTipForm({
        content:'呼叫失败,该患者已在它处呼叫!',
      });

      let id = JSON.parse(msg).id;
      const dataSource = this.state.currentList;
      this.setState({currentList:dataSource.filter(item=>item.key !== id)});
    }

    skipPatientSucceed = msg => {
      console.log("skipPatientSucceed");
      OperationTipForm.showTipForm({
        content:'设置过号成功!',
      });

      let id = JSON.parse(msg).id;

      if(this.state.tabIndex == "current"){
        for(let item of this.state.currentList){
          if(item.key == id){
            item.status = "过号";
            this.state.skipList.push(item);

            const dataSource = this.state.currentList;
            this.setState({currentList:dataSource.filter(item=>item.key !== id)});
            break;
          }
        }
      }
      else if(this.state.tabIndex == "skip"){
        for(let item in this.state.skipList){
          if(this.state.skipList[item].key == id){
            this.state.skipList[item].status = "过号";
          }
        }
      }
    };

    skipPatientFailed = msg => {
      console.log("skipPatientFailed");
      OperationTipForm.showTipForm({
        content:'设置过号失败!',
      });
    }

    treatedSucceed = msg => {
        console.log("treatedSucceed");
        OperationTipForm.showTipForm({
          content:'设置已就诊成功!',
        });

        let id = JSON.parse(msg).id;

        if(this.state.tabIndex == "current"){
          for(let item of this.state.currentList){
            if(item.key == id){
              this.state.doneList.push(item);

              const dataSource = this.state.currentList;
              this.setState({currentList:dataSource.filter(item=>item.key !== id)});
              break;
            }
          }
        }
        else if(this.state.tabIndex == "skip"){
          for(let item of this.state.skipList){
            if(item.key == id){
              this.state.doneList.push(item);

              const dataSource = this.state.skipList;
              this.setState({skipList:dataSource.filter(item=>item.key !== id)});
              break;
            }
          }
        }
    }

    treatedFailed = msg => {
      console.log("skipPatientFailed");
      OperationTipForm.showTipForm({
        content:'设置已就诊失败!',
      });
    }

    refreshPrompt = msg => {
      console.log("refreshPrompt");
      if(window.ExcuteCommand){
        let msg = {
          "type":8000,
          "counterId":window.localStorage.getItem("counterId")
        }
        window.ExcuteCommand(JSON.stringify(msg));

        this.setState({
          currentList:[],
          skipList:[],
          doneList:[],
        });
      }
    }

    getQueueSucceed = msg => {
      console.log("getQueueSucceed");
      window.localStorage.setItem("patientString",msg);
      let patientObj = parsePatientString2Object(msg);
      this.setState({
        currentList:patientObj.current,
        skipList:patientObj.skip,
        doneList:patientObj.done,
      });
    }

    getQueueFailed = msg => {
      console.log("getQueueFailed");
      OperationTipForm.showTipForm({
        content:'获取患者队列失败!',
      });
    }

    addPatientToQueue = msg => {
      console.log("addPatientToQueue");
      let data = JSON.parse(msg).data.result;
      for(let patient of data.remarks){
          let record = {
              "key":patient.id,
              "id":patient.sort,
              "name":patient.patientName,
              "status":"候诊",
          }
          this.state.currentList.push(record);
        }
        const dataSource = this.state.skipList;
        this.setState({skipList:dataSource.filter(item=>item.key !== id)});
    }

    // 呼叫患者
    handleCallingRequest = key => {
      if(window.ExcuteCommand){
        let msg = {
          "data":{
              "id":key,
              "patientName":this.state.doctor,
          },
          "type":7000,
          "counterId":window.localStorage.getItem("counterId")
        }
        window.ExcuteCommand(JSON.stringify(msg));
      }
    };

    handleSkipRequest = key => {
      if(window.ExcuteCommand){
        let msg = {
          "data":{
              "id":key,
              "patientName":this.state.doctor,
          },
          "type":7100,
          "counterId":window.localStorage.getItem("counterId")
        }
        window.ExcuteCommand(JSON.stringify(msg));
      }
    };

    handleTreatedRequest = key => {
      if(window.ExcuteCommand){
        let msg = {
          "data":{
              "id":key,
              "patientName":this.state.doctor,
          },
          "type":7200,
          "counterId":window.localStorage.getItem("counterId")
        }
        window.ExcuteCommand(JSON.stringify(msg));
      }
    };

    changeTab(key){
      console.log(key);
      this.setState({
        tabIndex:key,
      });
    }


    render(){
        return (
            <ContainerDiv>
              <Tabs size="default"  onChange={this.changeTab} >
                <TabPane tab="实时呼叫" key="current" >
                  <Table 
                      columns={this.columns} 
                      dataSource={this.state.currentList} 
                      pagination={ false }
                      size="middle"
                      align="center"
                      scroll={{y:'calc(100vh - 110px)'}}
                  />
                </TabPane>
                <TabPane tab="过号列表" key="skip">
                  <Table 
                      columns={this.columns} 
                      dataSource={this.state.skipList} 
                      pagination={ false }
                      size="middle"
                      align="center"
                      scroll={{y:'calc(100vh - 110px)'}}
                    />
                </TabPane>
                <TabPane tab="完成就诊" key="done">
                  <Table 
                      columns={this.columns_done} 
                      dataSource={this.state.doneList} 
                      pagination={ false }
                      size="middle"
                      align="center"
                      scroll={{y:'calc(100vh - 110px)'}}
                    />
                </TabPane>
              </Tabs>
            </ContainerDiv>
        )
    }
}

const ContainerDiv = styled.div`
  width: 100%;
  position: fixed;
  background-color: #F5F5F5;
`;
