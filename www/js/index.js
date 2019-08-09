const SERVER_REQUESTS = 'server/server_requests.php';
const LU = "Lyubomyr Bilyk";
const FERENCZ = "Ferencz Dominguez";
const NIK = "Nik Kershaw";
let elevatorLock = false;
let months = ['Jan', 'Feb', 'Mar', 'Apr', 'May', 'Jun', 'Jul', 'Aug', 'Sep', 'Oct', 'Nov', 'Dec'];

$(function () {
    updateTime();
    setInterval(updateTime, 1000);
    $('#sidebarToggle').on('click', function (event) {
        event.preventDefault();
        $("body").toggleClass('sidebar-toggled');
        $(".sidebar").toggleClass('toggled');
    });
    createLoginSectionDetails();

});

function updateTime() {
    let date = new Date();
    let time = ('0' + date.getHours()).slice(-2) + ':' + ('0' + date.getMinutes()).slice(-2) + ':' + ('0' + date.getSeconds()).slice(-2);
    let day = (months[date.getMonth()] + ' ' + ('0' + date.getDate()).slice(-2) + ' ' + date.getFullYear())
    let today = time + ' - ' + day;
    $('#datetime').html(today.toLocaleString());
}

function callToServer(data, dataType) {

    var response;
    $.ajax({
        url: SERVER_REQUESTS,
        type: 'POST',
        data: data,
        async: false,
        dataType: dataType,
        success: function (data) {
            response = data;
        },
    });
    return response;
}

function createLoginSectionDetails() {

    let user = getActiveUser();
    let fullName = user.split(' ');
    let firstName = fullName[0];
    if (user == '' || user == null) {
        // $('#loginSection').append(`<input class="btn btn-outline-light" type="button" value="Login" id="loginButton" onclick="window.location.href='login.php'">`);
    }   else {
        $('#loginSection').append(`<small>` + firstName + ` </small><input class=" ml-4 mr-0 btn btn-outline-light logout" type="button" value="Logout" id="logout" onclick="logout()">`);
        $('.login').toggle();
    }
}

function getActiveUser() {

    let user = localStorage.getItem('sessionUser');
    return user;
}

function logout() {

    localStorage.removeItem('sessionUser');
    window.location.href = 'logout.php';
}

function moveElevator(floor) {

    const UP = 'up';
    const DOWN = 'down';
    let travelTime = 200;

    floor = getFloorNumber(floor);
    let currentFloor = getCurrentFloor();

    let currentPosition = getFloorPosition(currentFloor);
    let destinationPosition = getFloorPosition(floor);

    let tracks = document.getElementsByClassName('elevator-light');



    if ((floor - currentFloor) === 0) {
        return;
    }

    updateFloor(floor);

    let direction = UP;
    if ((floor - currentFloor) < 0) {
        direction = DOWN;
    }
    $('.elevator-light').removeClass('done');

    switch (direction) {
        case UP:
            (function trackOn(onIndex) {
                $('.elevator-light').removeClass('done');
                setTimeout(function () {
                    let track = tracks[onIndex];
                    $(track).addClass('active');
                    (function trackOff(offIndex) {
                        setTimeout(function () {
                            let track = tracks[offIndex];
                            $(track).removeClass('active');
                            if (--offIndex + 1) {
                                if (offIndex !== (destinationPosition)) {
                                    trackOff(offIndex);
                                }
                                else {
                                    track = tracks[destinationPosition];
                                    $(track).addClass('done');
                                }
                                if (offIndex < destinationPosition) {
                                    elevatorLock = false;
                                }
                            }
                        }, travelTime++)
                    })(currentPosition);
                    if (--onIndex) {
                        if (onIndex !== (destinationPosition)) {
                            trackOn(onIndex);
                        }
                    }
                }, travelTime++)
            })(currentPosition);
            break;
        case DOWN:
            (function trackOn(onIndex) {
              $('.elevator-light').removeClass('done');
                setTimeout(function () {
                    let track = tracks[onIndex];
                    $(track).addClass('active');
                    (function trackOff(offIndex) {
                        setTimeout(function () {
                            let track = tracks[offIndex];
                            $(track).removeClass('active');
                            if (++offIndex) {
                                if (offIndex !== (destinationPosition)) {
                                    trackOff(offIndex);
                                }
                                else {
                                    track = tracks[destinationPosition];
                                    $(track).addClass('done');
                                }
                            }
                        }, travelTime++)
                    })(currentPosition);
                    if (++onIndex) {
                        if (onIndex !== (destinationPosition)) {
                            trackOn(onIndex);
                        }
                    }
                }, travelTime++)
            })(currentPosition);
            break;
    }
}

function getFloorNumber(floor) {

    return floor.length;
}

function getFloorPosition(floor) {

    const MAXFLOOR = 3;
    const TRACK_LENGTH = 11;

    let position = (MAXFLOOR - floor) * TRACK_LENGTH;
    return position;
}

$(window).scroll(function () {
    var scrollAmount = $(this).scrollTop();

    if (scrollAmount > 50) {
        $('.back-to-top').fadeIn();
    } else {
        $('.back-to-top').fadeOut();
    }
    if (scrollAmount > 200) {
        $('.back-to-top').css('visibility', 'visible');
    }
});

$('.back-to-top').click(function () {
    $("html, body").animate({
        scrollTop: 0
    }, 500);
    return false;
});

function updateFloor(floor) {

    let data = 'action=updateFloor&floor=' + floor;
    let dataType = 'text';
    callToServer(data, dataType);
}

function getCurrentFloor() {

    let data = 'action=getCurrentFloor';
    let dataType = 'text';
    let response = callToServer(data, dataType);
    return parseInt(response);
}
