document.addEventListener('DOMContentLoaded', function() 
{
    fetchData();
});

function fetchData() 
{
    fetch('/devices') // Fetching from the local server
        .then(response => response.json())
        .then(data => displayData(data))
        .catch(error => console.error('Error fetching data:', error));
}

function displayData(data) 
{
    const table = document.getElementById('device-table');
    // Clear existing table rows, except for the header
    while(table.rows.length > 1) 
        {
        table.deleteRow(1);
    }
    
    // Iterate over the data and create a table row for each device
    data.forEach((device, index) => 
    {
        const row = table.insertRow(-1); // Inserts a row at the end of the table
        const cell1 = row.insertCell(0); // Insert new cell for the device number
        const cell2 = row.insertCell(1); // Insert new cell for the MAC address
        
        cell1.textContent = index + 1; // Device number, starting at 1
        cell2.textContent = device; // MAC address
    });
}

function goBack() 
{
    window.location.href = "index.html";
}

function updateStatus(statusText) {
    document.getElementById('status').innerText = "Status: " + statusText;
}

function scanNetworks() {
    updateStatus("Scanning...")
    fetch('/scan')
        .then(response => response.json())
        .then(data => {
            const networksDiv = document.getElementById('networks');
            networksDiv.innerHTML = '';
            data.forEach((network, index) => {
                const networkDiv = document.createElement('div');
                networkDiv.classList.add('network');
                networkDiv.innerHTML = `
                    <strong>${network.ssid}</strong> (${network.rssi} dBm)
                    <br>
                    <button onclick="connectToNetwork('${network.ssid}')">Connect</button>
                `;
                networksDiv.appendChild(networkDiv);
            });
        });
    setTimeout(function() {
        updateStatus("Scan Complete!");
    }, 2500);
}

function connectToNetwork(ssid) {
    const password = prompt(`Enter password for ${ssid}:`);
    if (password !== null) {
        fetch('/connect', {
            method: 'POST',
            headers: {
                'Content-Type': 'application/json'
            },
            body: JSON.stringify({ssid, password })
        })
        .then(response => response.text())
        .then(message => {
            alert(message);
            checkStatus(); // Update status after connecting
        });
    }
}

function checkStatus() {
    fetch('/status')
        .then(response => response.text())
        .then(status => {
            updateStatus(status);
        });
}

// Ensure checkStatus is called when the script is loaded
document.addEventListener('DOMContentLoaded', (event) => {
    checkStatus();
});

