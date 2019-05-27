
const TIMELINE_CLASS = "timeline";

$(function() {
    createTimelineItems();
});

timelineTypes = {
    phase: createTLObjectPhase,
    week: createTLObjectWeek,
    blockLeft: createTLObjectBlockLeft,
    blockRight: createTLObjectBlockRight
};

timelineGlobals = {
    phase: '',
    week: '',
    title: '',
    date: '',
    description: '',
    user: ''
};

timeline = [
    {
        phase: [
            {
                week: [
                    {
                        type: timelineTypes.blockLeft,
                        title: 'Wiring',
                        date: 'May 17, 2019',
                        description: 'Wire the elevator and verify it was connected properly.',
                        user: 'Nik Kershaw'
                    },
                    {
                        type: timelineTypes.blockRight,
                        title: 'RPi Setup',
                        date: 'May 13, 2019',
                        description: 'Connect the raspberry pi to the network and change the password.',
                        user: 'Nik Kershaw'
                    },
                    {
                        type: timelineTypes.blockLeft,
                        title: 'Floor Nodes',
                        date: 'May 24, 2019',
                        description: 'Write software to send a command from one STM32 to another using CAN.',
                        user: 'Ferencz Dominguez'
                    },
                    {
                        type: timelineTypes.blockRight,
                        title: 'Software Front-End Setup',
                        date: 'May 17, 2019',
                        description: 'Build web-page template and create github repository. Add project plan to web-page.',
                        user: 'Lyubomyr Bilyk'
                    }
                ],
            },
            {
                week: [
                    {
                        type: timelineTypes.blockLeft,
                        title: 'Wiring',
                        date: 'May 17, 2019',
                        description: 'Finishing wiring elevator and all components.',
                        user: 'Nik Kershaw'
                    },
                    {
                        type: timelineTypes.blockRight,
                        title: 'Floor Nodes',
                        date: 'May 24, 2019',
                        description: 'Send CAN Message with floor value and get interrupt from push buttons.',
                        user: 'Ferencz Dominguez'
                    },
                    {
                        type: timelineTypes.blockLeft,
                        title: 'Software Front-End Setup',
                        date: 'May 17, 2019',
                        description: 'Finish off front-end template and upload repository to github.',
                        user: 'Lyubomyr Bilyk'
                    }
                ],
            },
            {
                week: [
                    {
                        type: timelineTypes.blockLeft,
                        title: 'Elevator Logic',
                        date: 'May 17, 2019',
                        description: 'Determine subsystems and design data-flow between subsystems.',
                        user: 'Nik Kershaw'
                    },
                    {
                        type: timelineTypes.blockRight,
                        title: 'Floor Nodes',
                        date: 'May 24, 2019',
                        description: 'Send CAN Message with floor value and get interrupt from push buttons.',
                        user: 'Ferencz Dominguez'
                    },
                    {
                        type: timelineTypes.blockLeft,
                        title: 'Software -  Front-End',
                        date: 'May 17, 2019',
                        description: 'Improve UI and add content to about and home pages.',
                        user: 'Lyubomyr Bilyk'
                    }
                ],
            },
        ]
    },
    {
        phase: [
            {
                week: [
                    {
                        type: timelineTypes.blockLeft,
                        title: 'Diagnostic Reporting',
                        date: 'June 14, 2019',
                        description: 'Start developing a program to log, monitor, and provide diagnostic information.',
                        user: 'Nik Kershaw'
                    },
                    {
                        type: timelineTypes.blockRight,
                        title: 'Software - Back-End',
                        date: 'June 14, 2019',
                        description: 'Setup database and determine data flow.',
                        user: 'Ferencz Dominguez'
                    },
                    {
                        type: timelineTypes.blockLeft,
                        title: 'Software Front-End',
                        date: 'June 14, 2019',
                        description: 'Create login/registration pages and restrict some content to authenticated users.',
                        user: 'Lyubomyr Bilyk'
                    }
                ],
            },
            {
                week: [
                    {
                        type: timelineTypes.blockLeft,
                        title: 'Diagnostic Reporting',
                        date: 'June 14, 2019',
                        description: 'Start developing a program to log, monitor, and provide diagnostic information.',
                        user: 'Nik Kershaw'
                    },
                    {
                        type: timelineTypes.blockRight,
                        title: 'Software - Back-End',
                        date: 'June 14, 2019',
                        description: 'Setup database and determine data flow.',
                        user: 'Ferencz Dominguez'
                    },
                    {
                        type: timelineTypes.blockLeft,
                        title: 'Software Front-End',
                        date: 'June 14, 2019',
                        description: 'Create login/registration pages and restrict some content to authenticated users.',
                        user: 'Lyubomyr Bilyk'
                    }
                ],
            },
        ]
    },
    {
        phase: [
            {
                week: [
                    {
                        type: timelineTypes.blockLeft,
                        title: 'Wiring/Setup',
                        date: 'May 17, 2019',
                        description: 'The elevator must be wired in order for the nodes to connect to the CAN bus. Wiring diagrams have been provided by faculty to follow.',
                        user: 'Nik Kershaw'
                    },
                    {
                        type: timelineTypes.blockRight,
                        title: 'Floor Nodes',
                        date: 'May 17, 2019',
                        description: 'There are individual STM32 boards that act as floor nodes. Floor nodes are in charge of sending a message to the CAN bus so the elevator is moved to that floor. To call the floor node a push button needs to be used and an LED needs to light up.',
                        user: 'Ferencz Dominguez'
                    }
                ],
            },
            {
                week: [
                    {
                        type: timelineTypes.blockLeft,
                        title: 'Wiring/Setup',
                        date: 'May 17, 2019',
                        description: 'The elevator must be wired in order for the nodes to connect to the CAN bus. Wiring diagrams have been provided by faculty to follow.',
                        user: 'Nik Kershaw'
                    },
                    {
                        type: timelineTypes.blockRight,
                        title: 'Floor Nodes',
                        date: 'May 17, 2019',
                        description: 'There are individual STM32 boards that act as floor nodes. Floor nodes are in charge of sending a message to the CAN bus so the elevator is moved to that floor. To call the floor node a push button needs to be used and an LED needs to light up.',
                        user: 'Ferencz Dominguez'
                    }
                ],
            },
        ]
    },
];

function createTimelineItems() {
    let weekNumber = 0;
    for (let i = 0; i < timeline.length; i++) {
        timelineGlobals.phase = "Phase " + (i + 1);
        $('.' + TIMELINE_CLASS).append(timelineTypes.phase());
        for (let j = 0; j < timeline[i].phase.length; j++) {
            weekNumber++;
            timelineGlobals.week = "Week " + (weekNumber);
            $('.' + TIMELINE_CLASS).append(timelineTypes.week());
            for (let k = 0; k < timeline[i].phase[j].week.length; k++) {
                timelineGlobals.title = timeline[i].phase[j].week[k].title;
                timelineGlobals.date = timeline[i].phase[j].week[k].date;
                timelineGlobals.description = timeline[i].phase[j].week[k].description;
                timelineGlobals.user = timeline[i].phase[j].week[k].user;
                $('.' + TIMELINE_CLASS).append(timeline[i].phase[j].week[k].type);
            }
        }
    }
}

function createTLObjectPhase(){

    let weekTemplate = '    <li>\
                                            <div class="tl-phase">' + timelineGlobals.phase + '</div>\
                                        </li>';
    return weekTemplate;
}

function createTLObjectWeek(){

   let weekTemplate = '    <li>\
                                            <div class="tl-week">' + timelineGlobals.week + '</div>\
                                        </li>';
   return weekTemplate;
}

function createTLObjectBlockLeft() {

    let blockLeftTemplate = '  <li>\
                                <div class="tl-circ"></div>\
                                <div class="timeline-panel">\
                                   <div class="tl-heading">\
                                        <h4>' + timelineGlobals.title + '</h4>\
                                        <p><small class="text-muted"><i class="fas fa-fw fa-calendar-day"></i>Due: ' + timelineGlobals.date + '</small></p>\
                                    </div>\
                                    <div class="tl-body">\
                                        <p>' + timelineGlobals.description + '</p>\
                                    </div>\
                                    <div class="person-responsible">\
                                            <small class="text-muted"><i class="fas fa-fw fa-user"></i>' + timelineGlobals.user + '</small>\
                                        </p>\
                                    </div>\
                                </div>\
                            </li>'
    return blockLeftTemplate;
}
function createTLObjectBlockRight() {

    let blockRightTemplate = '  <li class="timeline-inverted">\
                                <div class="tl-circ"></div>\
                                <div class="timeline-panel">\
                                   <div class="tl-heading">\
                                        <h4>' + timelineGlobals.title + '</h4>\
                                        <p><small class="text-muted"><i class="fas fa-fw fa-calendar-day"></i> Due: ' + timelineGlobals.date + '</small></p>\
                                    </div>\
                                    <div class="tl-body">\
                                        <p>' + timelineGlobals.description + '</p>\
                                    </div>\
                                    <div class="person-responsible">\
                                            <small class="text-muted"><i class="fas fa-fw fa-user"></i>' + timelineGlobals.user + '</small>\
                                        </p>\
                                    </div>\
                                </div>\
                            </li>'
    return blockRightTemplate;
}