const SERVER_REQUESTS = 'server/server_requests.php';
const LU = "Lyubomyr Bilyk";
const FERENCZ = "Ferencz Dominguez";
const NIK = "Nik Kershaw";

$(function () {
    $('#sidebarToggle').on('click', function (event) {
        event.preventDefault();
        $("body").toggleClass('sidebar-toggled');
        $(".sidebar").toggleClass('toggled');
    });
    createLoginSectionDetails();
});

function callToServer(data,dataType ) {

    var response;
    $.ajax({
        url: SERVER_REQUESTS,
        type: 'POST',
        data: data,
        async: false,
        dataType: dataType,
        success: function(data) {
            response = data;
        },
    });
    return response;
}

function createLoginSectionDetails() {

    let user = getActiveUser();
    let fullName = user.split(' ');
    let firstName = fullName[0];
    if(user == '' || user == null) {
        $('#loginSection').append( `<input class="btn btn-outline-light" type="button" value="Login" id="loginButton" onclick="window.location.href='login.php'">`);
    } else {
        $('#loginSection').append( `<small>` + firstName + ` </small>`);
    }
}
function getActiveUser() {

    let user = localStorage.getItem('sessionUser');
    return user;

}
function setProfileImage() {

    let user = localStorage.getItem('sessionUser');
    let userImage = '';

    switch (user) {
        case LU:
            userImage = '/img/lu.jpg';
            break;
        case FERENCZ:
            userImage = '/img/ferencz.jpg';
            break;
        case NIK:
            userImage = '/img/nik.jpg';
            break;
    }


}