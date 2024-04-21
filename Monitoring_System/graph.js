
async function fetchData() {
    const response = await fetch('getTemperatureData.php');
    const data = await response.json();
    return data;
}


async function updateGraph() {
    const data = await fetchData();

   
    const time = data.map(entry => moment(entry.time)); 
    const temperatures = data.map(entry => entry.temperature);

    
    const ctx = document.getElementById('temperatureChart').getContext('2d');
    const chart = new Chart(ctx, {
        type: 'line',
        data: {
            labels: timestamps,
            datasets: [{
                label: 'Temperature',
                data: temperatures,
                borderColor: 'blue',
                borderWidth: 2,
                fill: false
            }]
        },
        options: {
            scales: {
                x: {
                    type: 'time',
                    time: {
                        displayFormats: {
                        
                            second: 'ss', 
                        },
                    },
                },
                y: {
                    min: Math.min(...temperatures) - 1,
                    max: Math.max(...temperatures) + 1
                }
            }
        }
    });
}


setInterval(updateGraph, 50); 
