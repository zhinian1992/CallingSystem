import React from 'react';
import { Row, Spin } from 'antd';
import "antd/dist/antd.css";
import styled, { createGlobalStyle } from "styled-components";

export default class InitView extends React.Component{
    constructor(props){
        super(props);

        this.state = {
            tips:"正在连接叫号服务器",
            tipShow:'block'
        }

        window.connectionSucceed = (params) => this.connectionSucceed(params);
        window.connectionFailed = (params) => this.connectionFailed(params);
        window.receiveOrgData = (params) => this.receiveOrgData(params);
    }
    
    componentDidMount(){
        console.log("login componentDidMount");
        // 注册回调
        if(window.RegisterCallback){
            console.log("login componentDidMount register");
            // 注册连接成功回调
            window.RegisterCallback(JSON.stringify({ type:1001, method:"connectionSucceed" }));
            // 注册连接失败回调
            window.RegisterCallback(JSON.stringify({ type:1002, method:"connectionFailed" }));
            // 注册获取机构科室信息成功回调
            window.RegisterCallback(JSON.stringify({ type:5001, method:"receiveOrgData" }));
        }
        // 连接叫号服务
        setTimeout(this.connect, 300);
    }

    connect(){
        if(window.ExcuteCommand){
            console.log('connect');
            window.ExcuteCommand("connect");
        }
    }

    //连接叫号服务成功
    connectionSucceed = msg => {
        console.log("connectionSucceed receive :" + msg);
        this.setState({
            tips:"连接成功!正在获取机构信息"
        });
        let request = {
            type:5000
        }
        window.ExcuteCommand(JSON.stringify(request));
    }

    //连接叫号服务失败
    connectionFailed = msg => {
        console.log("connectionFailed");
        this.setState({
            tips:"连接叫号服务失败!请联系管理员",
            tipShow:'none'
        });

        setTimeout(this.connect, 5000);
    }

    //接收机构科室列表成功回调
    receiveOrgData = msg => {
        console.log("receiveOrgData receive :" + msg);
        window.localStorage.setItem("org",msg);
        this.props.history.push('/login');
    }

    render(){
        return (
            <ContainerDiv>
                <TipContainer>
                    <div style={{display: this.state.tipShow}} >
                        <Spin size="default" />
                    </div>
                    <h2 style={{color:"#008B8B"}}>{this.state.tips}</h2>
                </TipContainer>
            </ContainerDiv>
        )
    }
}
    
const ContainerDiv = styled.div`
    position: absolute;
    height: 100%;
    width: 100%;
    background-color:#F5F5F5;
`;

const TipContainer = styled.div`
    position: relative;
    top: 50%;
    text-align:center;
`;