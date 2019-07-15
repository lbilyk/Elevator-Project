
$(function () {
    setInterval(getLogDataFromServer, 1000);
}

function getLogDataFromServer() {

    let data = 'action=getLogData';
    let dataType = 'json';
    let response = callToServer(data,dataType);
    displayLogData(response);
}

function displayLogData(data) {

    $('#logData').empty();
    for (let i = 0; i < data.length; i++) {
        let timestamp = data[i].Timestamp;
        let command = data[i].Command;
        let floor = data[i].Floor;

        $('#logData').append('  <a href="#" class="list-group-item list-group-item-action flex-column align-items-start">\
                                    <div class="d-flex w-100 justify-content-between">\
                                        <small class="text-muted ">TimeStamp: ' + timestamp +'</small>\
                                    </div>\
                                <p class="mb-1">Command: '+ command + ' ' + floor + '</p>\
    </a>\
  ');
    }
}