import React, { Component } from 'react';
import './App.css';
import appConfig from './appConfig';

class DocSelect extends Component {
    constructor(props) {
        super(props);
        this.state = {
            apiData: [{
                status: [],
                user: [],
                _id: [],
                name: [],
                modification_date: []
            }],
        }
    }
    getDocsFromApi() {
        fetch(appConfig.ApiServer)
            .then(response => response.json())
            .then(data => this.setState({ apiData: data }));
    }
    componentDidMount() {
        this.interval = setInterval(() => this.getDocsFromApi(), 250);
    }
    componentWillUnmount() {
        clearInterval(this.interval);
    }
    render() {
        const { apiData } = this.state;
        console.log(apiData.length);
        return (
            <div className="App">
                <header className="App-header">
                    <div>Docs in database: {apiData.length}</div>
                    <div>Document 01 Data</div>
                    <div>Filename: {apiData[0].name}</div>
                    <div>Status: {apiData[0].status}</div>
                    <div>Modification Date: {apiData[0].modification_date}</div>
                    <div>Last Edit: {apiData[0].user}</div>
                </header>
            </div>
        );
    }
}

export default DocSelect;