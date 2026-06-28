let client;

const mqttStatus =
document.getElementById("mqttStatus");

const temperatureEl =
document.getElementById("temperature");

const humidityEl =
document.getElementById("humidity");

const espStatus =
document.getElementById("espStatus");

const weatherStatus =
document.getElementById("weatherStatus");

const lastUpdate =
document.getElementById("lastUpdate");

const alertBox =
document.getElementById("alertBox");

const logContainer =
document.getElementById("logContainer");

const labels = [];
const tempData = [];
const humData = [];

const ctx =
document.getElementById("weatherChart");

const chart = new Chart(ctx,{
type:"line",
data:{
labels:labels,
datasets:[
{
label:"Temperature (°C)",
data:tempData,
borderColor:"#38bdf8",
backgroundColor:"rgba(56,189,248,.2)",
fill:true,
borderWidth:3,
tension:.4
},
{
label:"Humidity (%)",
data:humData,
borderColor:"#f43f5e",
backgroundColor:"rgba(244,63,94,.15)",
fill:true,
borderWidth:3,
tension:.4
}
]
},
options:{
responsive:true,
maintainAspectRatio:false,
plugins:{
legend:{
labels:{
color:"white"
}
}
},
scales:{
x:{
ticks:{
color:"white"
}
},
y:{
ticks:{
color:"white"
}
}
}
}
});

function connectMQTT(){

const host =
"wss://df9575cf81dd4ea39cc9fe88f106c3ab.s1.eu.hivemq.cloud:8884/mqtt";

client = mqtt.connect(host,{
username:"syopijh",
password:"Treasure12pjh"
});

client.on("connect",()=>{

mqttStatus.innerHTML =
"🟢 MQTT Connected";

mqttStatus.classList.remove("disconnected");
mqttStatus.classList.add("connected");

client.subscribe("weather/data");

});

client.on("message",(topic,message)=>{

const data =
JSON.parse(message.toString());

const temp =
data.temperature - 10;

const hum =
data.humidity - 10;

temperatureEl.innerHTML =
temp.toFixed(1) + " °C";

humidityEl.innerHTML =
hum.toFixed(1) + " %";

espStatus.innerHTML =
"🟢 Online";

const time =
new Date().toLocaleTimeString();

lastUpdate.innerHTML =
time;

if(temp > 30){

weatherStatus.innerHTML =
"🔥 Hot";

alertBox.innerHTML =
"⚠ High Temperature Detected";

}
else if(temp < 20){

weatherStatus.innerHTML =
"❄ Cold";

alertBox.innerHTML =
"⚠ Low Temperature";

}
else{

weatherStatus.innerHTML =
"✅ Normal";

alertBox.innerHTML =
"✅ Environment Stable";

}

labels.push(time);
tempData.push(temp);
humData.push(hum);

if(labels.length > 20){

labels.shift();
tempData.shift();
humData.shift();

}

chart.update();

const log =
document.createElement("div");

log.className =
"log-item";

log.innerHTML =
`[${time}] Temp : ${temp.toFixed(1)}°C | Hum : ${hum.toFixed(1)}%`;

logContainer.prepend(log);

});

client.on("error",(err)=>{

console.log(err);

});

}

function disconnectMQTT(){

if(client){

client.end();

mqttStatus.innerHTML =
"🔴 MQTT Disconnected";

mqttStatus.classList.remove("connected");
mqttStatus.classList.add("disconnected");

espStatus.innerHTML =
"🔴 Offline";

}

}

function clearLogs(){

logContainer.innerHTML = "";

}