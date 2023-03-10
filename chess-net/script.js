fetch(chrome.runtime.getURL('/index.html'))
    .then(response => response.text())
    .then(data => {
        document.getElementById('root').innerHTML = data;
       
    }).catch(err => {
        // handle error
    });