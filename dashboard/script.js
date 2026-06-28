// ======================================
// MQTT CONFIG
// ======================================

const options = {

    username: "syopijh",

    password: "Treasure12pjh",

    reconnectPeriod: 3000,

    connectTimeout: 10000,

    clean: true

};

const client = mqtt.connect(

"wss://df9575cf81dd4ea39cc9fe88f106c3ab.s1.eu.hivemq.cloud:8884/mqtt",

options

);

// ======================================
// HTML
// ======================================

const mqttStatus =
document.getElementById("mqttStatus");

const tempValue =
document.getElementById("tempValue");

const humValue =
document.getElementById("humValue");

const distanceValue =
document.getElementById("distanceValue");

const statusValue =
document.getElementById("statusValue");

const device =
document.getElementById("device");

const time =
document.getElementById("time");

const encryptedTemp =
document.getElementById("encryptedTemp");

const decryptedTemp =
document.getElementById("decryptedTemp");

const logTable =
document.getElementById("logTable");

// ======================================
// CHART
// ======================================

const ctx =
document.getElementById("weatherChart");

const weatherChart =
new Chart(ctx,{

type:"line",

data:{

labels:[],

datasets:[

{

label:"Temperature",

data:[],

borderWidth:3,

tension:.3

},

{

label:"Humidity",

data:[],

borderWidth:3,

tension:.3

}

]

},

options:{

responsive:true,

animation:true,

plugins:{

legend:{

labels:{

color:"white"

}

}

},

scales:{

x:{

ticks:{color:"white"}

},

y:{

ticks:{color:"white"}

}

}

}

});

// ======================================
// CONNECT
// ======================================

client.on("connect",()=>{

console.log("MQTT Connected");

mqttStatus.innerHTML="Connected";

mqttStatus.className="badge bg-success";

client.subscribe("weather/data");

});

// ======================================
// DISCONNECT
// ======================================

client.on("reconnect",()=>{

mqttStatus.innerHTML="Reconnecting";

mqttStatus.className="badge bg-warning";

});

client.on("offline",()=>{

mqttStatus.innerHTML="Offline";

mqttStatus.className="badge bg-danger";

});

client.on("error",(err)=>{

console.log(err);

});

// ======================================
// RECEIVE DATA
// ======================================

client.on("message",(topic,message)=>{

let data =
JSON.parse(message.toString());

//==========================
// DECRYPT
//==========================

let temp =
data.temperature-10;

let hum =
data.humidity-10;

let distance =
data.distance-10;

//==========================

tempValue.innerHTML=
temp.toFixed(1)+" °C";

humValue.innerHTML=
hum.toFixed(1)+" %";

distanceValue.innerHTML=
distance+" cm";

statusValue.innerHTML=
data.status;

device.innerHTML=
data.device;

time.innerHTML=
data.time;

encryptedTemp.innerHTML=
data.temperature.toFixed(1)+" °C";

decryptedTemp.innerHTML=
temp.toFixed(1)+" °C";

//==========================
// STATUS COLOR
//==========================

statusValue.className="";

if(data.status=="Safe"){

statusValue.classList.add("safe");

}

else if(data.status=="Nearby"){

statusValue.classList.add("nearby");

}

else{

statusValue.classList.add("close");

}

//==========================
// CHART
//==========================

weatherChart.data.labels.push(data.time.substring(11));

weatherChart.data.datasets[0].data.push(temp);

weatherChart.data.datasets[1].data.push(hum);

if(weatherChart.data.labels.length>15){

weatherChart.data.labels.shift();

weatherChart.data.datasets[0].data.shift();

weatherChart.data.datasets[1].data.shift();

}

weatherChart.update();

//==========================
// TABLE
//==========================

let row=`

<tr>

<td>${data.time}</td>

<td>${temp.toFixed(1)} °C</td>

<td>${hum.toFixed(1)} %</td>

<td>${distance} cm</td>

<td>${data.status}</td>

</tr>

`;

logTable.insertAdjacentHTML(

"afterbegin",

row

);

if(logTable.rows.length>10){

logTable.deleteRow(10);

}

});