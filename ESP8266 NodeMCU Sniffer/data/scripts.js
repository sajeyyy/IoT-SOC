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
    const container = document.getElementById('device-list');
    container.innerHTML = ''; // Clear existing content

    data.forEach(device => {
        const item = document.createElement('li');
        item.textContent = device;
        container.appendChild(item);
    });
}


