import React, { Component } from 'react';
import Popup from 'reactjs-popup';
import './App.css';
import appConfig from './appConfig';

class DocSelect extends Component {
    constructor(props) {
        super(props);
        this.state = {
            modalCreate: false,
            createValue: '',
            apiData: [{
                status: [],
                user: [],
                _id: [],
                name: [],
                modification_date: []
            }],
        };
    }
    openCreate () {
        this.setState({ modalCreate: true })
    }
    closeCreate () {
        this.setState({ modalCreate: false })
    }
    handleChange(event) {
        this.setState({createValue: event.target.value});
    }
    getDocsFromApi() {
        fetch(appConfig.ApiServer)
            .then(response => response.json())
            .then(data => this.setState({ apiData: data }));
    }
    delDocsFromApi(docId) {
        fetch(appConfig.ApiServer + docId, {
            method: 'DELETE',
        })
            .then(response => response.json());
    }
    addDocsToApi(docName) {
        fetch(appConfig.ApiServer, {
            method: 'POST',
            headers: {
                Accept: 'application/json',
                'Content-Type': 'application/json',
            },
            body: JSON.stringify({
                name: docName,
            }),
        });
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
            let disableButton = false;

            if (apiData[i].status === "used") {
                disableButton = true;
            }

            docList.push(<div className="documentBox" key={i}>
                <h3>{apiData[i].name}</h3>
                <p>Status: {apiData[i].status}</p>
                <a href="http://localhost:3002/editor"><button className="small green button">View</button></a><br/>
                <a href="http://localhost:3002/editor"><button className="small blue button" disabled={disableButton}>Edit</button></a><br/>
                <button className="small red button" disabled={disableButton} onClick={this.delDocsFromApi.bind(this, apiData[i]._id)}>Delete</button>
            </div>);
        }
        return docList;
    };

    render() {
        const { apiData } = this.state;
        console.log(apiData.length);
        return (
            <div className="App">
                <header className="App-header">
                    <button className="button" onClick={this.openCreate.bind(this)}>Create New Document</button>
                    <Popup open={this.state.modalCreate} closeOnDocumentClick onClose={this.closeCreate.bind(this)}>
                        <div className="modal">
                            <div className="header">Create New Document</div>
                            <div className="content">

                                <form onSubmit={this.addDocsToApi.bind(this, this.state.createValue)}>
                                    <label className="formCreate">File Name: <input type="text" value={this.state.createValue} onChange={this.handleChange.bind(this)} />
                                    </label>
                                    <input className="small red button" type="submit" value="Submit" />
                                </form>

                            </div>
                        </div>
                    </Popup>
                    <div className="documentList">
                        {this.createDocsList()}
                    </div>
                </header>
            </div>
        );
    }
}

export default DocSelect;