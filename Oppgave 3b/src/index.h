const char MAIN_page[] PROGMEM = R"=====(
<!DOCTYPE html>
<html>
<style>
.card{
    max-width: 500px;
     min-height: 250px;
     background: #333;
     padding: 30px;
     box-sizing: border-box;
     color: #FFC;
     margin:20px;
     box-shadow: 0px 2px 18px -4px rgba(0,0,0,0.75);
}
</style>
<body>

<div class="card">
  <h4>Sensorverdier fra ESP32:</h4><br>
  <h1>Potentiometer-verdi: <span id="val1">0</span> V</h1><br>
  <h1>Fotosensor-verdi: <span id="val2">0</span> V</h1><br>
</div>
<script>
    requestData(); // get intial data straight away 
  
    // request data updates every 10 milliseconds
    setInterval(requestData, 10);

    function requestData() {

      var xhr = new XMLHttpRequest();
      xhr.open('GET', 'sensors');

      xhr.onload = function() {
        if (xhr.status === 200) {

          if (xhr.responseText) { // if the returned data is not null, update the values

            var data = JSON.parse(xhr.responseText);

            document.getElementById("val1").innerText = data.val1;
            document.getElementById("val2").innerText = data.val2;

          } 
      };
      
      xhr.send();
    }
    
  </script>
</body>
</html>
)=====";