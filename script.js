const tempChart = new Chart(
document.getElementById("tempChart"),
{
type:"line",
data:{
labels:["1","2","3","4","5"],
datasets:[
{
label:"Suhu",
data:[28,29,30,31,30]
}
]
}
}
);

const humChart = new Chart(
document.getElementById("humChart"),
{
type:"line",
data:{
labels:["1","2","3","4","5"],
datasets:[
{
label:"Kelembapan",
data:[70,71,74,75,76]
}
]
}
}
);

document
.getElementById("ledOn")
.addEventListener("click",()=>{

addLog("LED ON");

});

document
.getElementById("ledOff")
.addEventListener("click",()=>{

addLog("LED OFF");

});

function addLog(text){

const li=document.createElement("li");

li.innerText=
new Date().toLocaleTimeString()
+
" - "
+
text;

document
.getElementById("logList")
.prepend(li);

}