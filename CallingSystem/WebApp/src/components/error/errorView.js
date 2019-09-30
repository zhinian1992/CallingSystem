import React from 'react';
import ReactDOM from 'react-dom';


export default {
    dom: null,

    showTipForm () {
        this.close();
 
        this.dom = document.createElement('div');
 
        // JSX代码
        const JSXdom = (
            <div>
                <div style={styles.mask} />
                <div style={styles.modalWrap}>
                    <div style={styles.modal}>
                        <h2>该账号已在其他电脑登录!</h2>
                    </div>
                </div>
            </div>
        );
 
        ReactDOM.render(JSXdom, this.dom);
        document.body.appendChild(this.dom);
    },
 
    close () {
        this.dom && this.dom.remove();
    }
}

const styles = {
    mask: {
        position: 'fixed',
        top: 0,
        right: 0,
        left: 0,
        bottom: 0,
        backgroundColor: 'rgba(0, 0, 0, 0.65)',
        height: '100%',
        zIndex: 1000,
    },
    modalWrap: {
        position: 'fixed',
        top: 0,
        right: 0,
        left: 0,
        bottom: 0,
        zIndex: 1000,
    },
    modal: {
        fontSize: 14,
        padding: 20,
        width: 320,
        height: 150,
        margin: '100px auto 0',
        backgroundColor: '#fff',
        borderRadius: 4,
        overflow: 'hidden',
        textAlign: 'center',
    },
  };
  