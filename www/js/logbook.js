
$(function() {
    let data = "action=getLogbookData";
    let dataType = 'text';
    let response = callToServer(data,dataType);
    createLogbookEntries(response);
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