import React from 'react';
import {
    BrowserRouter, 
    Route, 
    Switch,
    Redirect
} from 'react-router-dom';
import LoginView from './login/loginView';
import PatientView from './patient/patientView';
import InitView from './initialize/initView';

const App = () => (
    <BrowserRouter>
        <Switch>
            <Route path='/' render={() => <Redirect to="/init" />} exact></Route>
            <Route path="/init" component={InitView} />
            <Route path="/login" component={LoginView} />
            <Route path="/patient" component={PatientView} />
        </Switch>
    </BrowserRouter>
);

export default App;