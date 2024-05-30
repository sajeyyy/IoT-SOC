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

function displayData(data) {
    const table = document.getElementById('device-table');
    // Clear existing table rows, except for the header
    while(table.rows.length > 1) {
        table.deleteRow(1);
    }
    
    // Iterate over the data and create a table row for each device
    data.forEach((device, index) => {
        const row = table.insertRow(-1); // Inserts a row at the end of the table
        const cell1 = row.insertCell(0); // Insert new cell for the device number
        const cell2 = row.insertCell(1); // Insert new cell for the MAC address
        
        cell1.textContent = index + 1; // Device number, starting at 1
        cell2.textContent = device; // MAC address
    });
}

