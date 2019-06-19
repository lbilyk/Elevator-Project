
$(function() {
    let data = "action=getLogbookData";
    let dataType = 'text';
    let response = callToServer(data,dataType);
    localStorage.setItem('logbookEntries',response);
    createLogbookEntries(response);
    addFilterOptions(response);
});

function createLogbookEntries(entriesJSON) {

    let entries = JSON.parse(entriesJSON);
    console.log(entries);

    for(let i = 0; i < entries.length; i++) {

        let user = entries[i].username;
        let date = entries[i].date;
        let entry = entries[i].entry;

        $('#logbookEntries').append('   <a href="#" class="list-group-item list-group-item-action flex-column align-items-start">\
                                        <div class="d-flex w-100 justify-content-between">\
                                            <small class="text-muted ">' + date + '</small>\
                                        </div>\
                                        <p class="mb-1">' + entry + '</p>\
                                        <small class="text-muted "><p class="text-right">' + user + '</p></small>\
                                    </a>');
    }
}

function checkIfEntryExists() {

    let entryText = $('#logbookEntry').prop('value');

    if(entryText.length > 0) {
        addLogbookEntry(entryText);
    }
    else {
        alert("You can't submit nothing!");
        return;
    }
}
function addLogbookEntry(entryText) {

    let user = localStorage.getItem('sessionUser');
    let data = "action=addLogbookEntry&entry=" + entryText + "&user=" + user;
    let dataType = "text";
    callToServer(data,dataType);
    location.reload();
}

function addFilterOptions(entriesJSON) {

    const DATETIME_TO_DATE = 10;
    let dates = [];
    let names = [];
    let entries = JSON.parse(entriesJSON);
    for(let i = 0; i < entries.length; i++) {
        dates[i] = entries[i].date;
        names[i] = entries[i].username;
    }
    dates.sort((a,b)=>a-b);
    names.sort((a,b)=>a-b);

    let minDate = dates[0];
    let maxDate = dates.splice(-1)[0];
    let uniqueNames = names.filter((item,index)=> names.indexOf(item) === index);

    $('#minDate').prop('value',minDate.slice(0,DATETIME_TO_DATE));
    $('#maxDate').prop('value',maxDate.slice(0,DATETIME_TO_DATE));

    $('#nameSelect').append('<option selected>Filter by Name</option>');
    $.each(uniqueNames,function(key,value) {
        $('#nameSelect').append($('<option></option>').attr("value",value).text(value));
    })
}

function filterLogbookEntries() {

    let minDate = $('#minDate').prop('value');
    let maxDate = $('#maxDate').prop('value');
    let name = $('#nameSelect option:selected').text();
    let entriesJSON = localStorage.getItem('logbookEntries');
    let entries = JSON.parse(entriesJSON);
    let filteredEntries = entries;
    const filterNameDefault = "Filter by Name";

    $('#logbookEntries').empty();

    let filterMinDate = new Date(minDate);
    let filterMaxDate = new Date(maxDate);


    for(let i = 0; i < entries.length; i++) {
        let date = new Date(entries[i].date);
        if((date < filterMinDate - 1) || (date > filterMaxDate + 1) || (name !== entries[i].username && name !== filterNameDefault)) {
            filteredEntries[i] = null;
        }
    }
    let filter = filteredEntries.filter(Boolean);
    createLogbookEntries(JSON.stringify(filter));
}

// function addLogbookEntry(entries) {
//
//     alert(entries);
//     let entriesKJSON = JSON.parse(entries);
//
// }