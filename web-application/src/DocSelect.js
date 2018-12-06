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
    createDocsList() {
        let docList = [];
        const { apiData } = this.state;

        for (let i = 0; i < apiData.length; i++) {
            docList.push(<div className="documentBox" key={i}><h3>{apiData[i].name}</h3><p>{apiData[i].status}</p></div>);
        }
        return docList;
    };
    render() {
        const { apiData } = this.state;
        console.log(apiData.length);
        return (
            <div className="App">
                <header className="App-header">
                    <div className="documentList">
                        {this.createDocsList()}
                    </div>
                </header>
            </div>
        );
    }
}

export default DocSelect;