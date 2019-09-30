import React from 'react';
import { 
    Row,
    Cascader,
    Input,
    Icon,
    Button,
    Form,
    PageHeader
} from 'antd';
import "antd/dist/antd.css";
import parseOrgString2List from "./orgdataParser";
import styled, { createGlobalStyle } from "styled-components";


let width = 600;
let height = 400;

//递归遍历查找当前级联选择器所选项
function search(obj,labels){
    if(labels.length > 1){
        for(let item of obj){
            if(item.label == labels[0]){
                labels.shift();
                return search(item.children,labels);
            }
        }
    }
    else if(labels.length == 1){
        for(let item of obj){
            if(item.label == labels[0]){
                return item.code;
            }
        }
    }
    else 
        return null;
}

class LoginView extends React.Component{
    constructor(props){
        super(props);
        this.state = {
            orgList:parseOrgString2List(window.localStorage.getItem('org')),
            orgValue:window.localStorage.getItem('orgValue')==null?[]:window.localStorage.getItem('orgValue').split(','),
            userName:window.localStorage.getItem('userName'),
            password:window.localStorage.getItem('password'),
            counterId:null
        }
        //回调方法
        window.loginSucceed = (params) => this.loginSucceed(params);
        window.loginFailed = (params) => this.loginFailed(params);
        window.connectionFailed = (params) => this.connectionFailed(params);
    }
    componentDidMount(){
        // 修改浏览器大小
        if(window.ResizeBrowser){
            window.ResizeBrowser(JSON.stringify({width:width,height:height}));
        }
        if(window.RegisterCallback){
            // 注册登陆成功回调
            window.RegisterCallback(JSON.stringify({type:6001,method:"loginSucceed"}));
            // 注册登陆失败回调
            window.RegisterCallback(JSON.stringify({type:6002,method:"loginFailed"}));
            // 注册网络异常回调
            window.RegisterCallback(JSON.stringify({type:1001,method:"connectionFailed"}));
        }
        if(this.state.userName == ""){
            this.state.userName = "请输入用户名";
        }
        if(this.state.password == ""){
            this.state.password = "请输入密码";
        }
    }

    // 登录成功回调
    loginSucceed = msg => {
        console.log("loginSucceed receive msg-->" + msg);
        window.localStorage.setItem('patientString',msg);

        this.props.history.push('/patient');
    }

    // 登录失败回调
    loginFailed = msg => {
        console.log("loginFailed receive msg-->" + msg);
    }

    // 连接失败回调
    connectionFailed = msg => {
        console.log("connectionFailed receive msg-->" + msg);
    }

    displayRender = labels => {
        if(labels.length == 4){
            window.localStorage.setItem('orgValue',labels)
            window.localStorage.setItem('counterId',search(this.state.orgList,labels));
            return labels.toString();
        }
    }

    handleSubmit = e => {
        e.preventDefault();
        this.props.form.validateFields((err, values) => {
          if (!err) {
            if(window.ExcuteCommand){
                let msg = {
                    "data":{
                        "loginName":values.userName,
                        "password":values.password,
                        "counterId":window.localStorage.getItem("counterId")
                    },
                    "type":6000
                }
                console.log(msg);
                window.ExcuteCommand(JSON.stringify(msg));
                window.localStorage.setItem('userName',values.userName);
                window.localStorage.setItem('password',values.password);
            }
          }
        });
    };

    render(){
        const { getFieldDecorator } = this.props.form;
        
        return (
            <LoginForm>
                <br />
                <Row type="flex" justify="center" >
                    <PageHeader title="分诊叫号" />
                </Row>
                <br />
                <Row type="flex" justify="center" >
                    <Cascader
                        displayRender={this.displayRender}
                        defaultValue={this.state.orgValue}
                        style={styles.controls}
                        options={this.state.orgList}
                        expandTrigger="hover"
                        placeholder="请选择科室"
                    />
                </Row>
                <br />
                <Row type="flex" justify="center" >
                    <Form onSubmit={this.handleSubmit}>
                        <Form.Item>
                            {
                                getFieldDecorator('userName', {
                                    initialValue: this.state.userName,
                                    rules: [
                                        { 
                                            required: true, 
                                            message: '请输入用户名!' 
                                        }
                                    ],
                                    })(
                                        <Input
                                            prefix={<Icon type="user" />}
                                            placeholder="请输入用户名"
                                            style={styles.controls}
                                        />,
                            )}
                        </Form.Item>
                        <Form.Item>
                            {
                                getFieldDecorator('password', {
                                    initialValue: this.state.password,
                                    rules: [
                                        { 
                                            required: true, 
                                            message: '请输入密码!' 
                                        }
                                    ],
                                    })(
                                        <Input.Password
                                            prefix={<Icon type="lock" />}
                                            placeholder="请输入密码"
                                            style={styles.controls}
                                        />,
                            )}
                        </Form.Item>
                        <Form.Item>
                            <Button 
                                type="primary" 
                                style={styles.controls}
                                onClick={this.handleSubmit}
                            >
                            登录
                            </Button>
                        </Form.Item>
                    </Form>
                </Row>
            </LoginForm>
        )
    }
}

export default Form.create()(LoginView);

const LoginForm = styled.div`
    height: 100%;
    width: 100%;
    position: fixed;
    background-color: #F5F5F5;
`;

var styles = {
    controls:{
        width:300
    }
}