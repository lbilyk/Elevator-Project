const SERVER_REQUESTS = 'server/server_requests.php';
const LU = "Lyubomyr Bilyk";
const FERENCZ = "Ferencz Dominguez";
const NIK = "Nik Kershaw";
let currentFloor = 1;

$(function () {
    let date = new Date();
    $('#datetime').html(date.toLocaleString());
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

function moveElevator(floor) {

    let moveHeight = floor * 200;
    let animation = Math.abs(currentFloor - floor) * 1000;
    if (floor == currentFloor) {
        return;
    }

    $("#doorRight").removeClass("open-right");
    $("#doorLeft").removeClass("open-left");

    setTimeout(function(){
        $("#elevatorContainer").css("transition","all " + animation + "ms linear");
        $("#elevatorContainer").css("bottom",moveHeight - 128 +"px");
        currentFloor = floor;
        setTimeout(function(){

            $("#doorRight").addClass("open-right");
            $("#doorLeft").addClass("open-left");

        },animation);
        },300);
}

$(window).scroll(function() {
    var scrollAmount = $(this).scrollTop();

    if (scrollAmount > 50) {
        $('.back-to-top').fadeIn();
    }
    else {
        $('.back-to-top').fadeOut();
    }
    if(scrollAmount > 200) {
        $('.back-to-top').css('visibility','visible');
    }
});

$('.back-to-top').click(function () {
    $("html, body").animate({
        scrollTop: 0
    }, 500);
    return false;
});