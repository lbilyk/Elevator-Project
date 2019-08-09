
$(function () {
    setInterval(getLogDataFromServer, 1000);
    getStatisticalDataFromServer();

});

function getLogDataFromServer() {

    let data = 'action=getLogData';
    let dataType = 'text';
    let response = callToServer(data,dataType);
    console.log(JSON.parse(response));
    displayLogData(JSON.parse(response));
}

function getStatisticalDataFromServer() {

    let data = 'action=getStatData';
    let dataType = 'json';
    let response = callToServer(data,dataType);
    plotStatData(response);

}

function displayLogData(data) {

    $('#logData').empty();
    let iterations = data.length;
    const maxIterations = 100;

    if(data.length > maxIterations) {
        iterations = maxIterations;
    }
    for (let i = iterations; i > 0; i--) {
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

function plotStatData(statData) {

    let floor1 =  statData[0].call_count;
    let floor2 =  statData[1].call_count;
    let floor3 =  statData[2].call_count;

    var data = google.visualization.arrayToDataTable([
        ["Floor", "Call Count", { role: "style" } ],
        ["Floor 1", floor1, "#cd7d72"],
        ["Floor 2", floor2, "#376c81"],
        ["Floor 3", floor3, "#fdd333"],
    ]);

    var view = new google.visualization.DataView(data);
    view.setColumns([0, 1,
        { calc: "stringify",
            sourceColumn: 1,
            type: "string",
            role: "annotation" },
        2]);

    var options = {
        title: "Floor Call Count",
        width: 600,
        height: 400,
        bar: {groupWidth: "95%"},
        legend: { position: "none" },
    };
    var chart = new google.visualization.BarChart(document.getElementById("statData"));
    chart.draw(view, options);
}