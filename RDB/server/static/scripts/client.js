const urlListHotel = 'http://localhost:5002/list_hotel'
const urlListRoom = 'http://localhost:5002/list_room'
const urlGetInfoHotel = 'http://localhost:5002/info_hotel'


const navigation = document.querySelector('#navigation')
const infoFilter = document.querySelector('#info_filter')
const content = document.querySelector('#content')
let currentIdHotel = 0


printButtonHotel(urlListHotel)

async function getQueru(url) {
    return fetch(url)
    .then(response => response.json())
    .then(json => json)
    .catch(error => console.error(error))
}

async function postQuary(url, object) {
    return fetch(url, {
        method: 'POST',
        body: JSON.stringify(object),
        headers: {
            'Content-Type': 'application/json'
        }
    })
    .then(response => response.json())
    .then(json => console.log(json)).
    catch(error => console.error(error))
}

async function printButtonHotel(url) {
    const list_button = await getQueru(url)
    for (let key in list_button) {
        const btn = document.createElement('button')    
        btn.innerHTML = `${list_button[key].name}`
        btn.classList.add('hotelBtn')
        navigation.append(btn)
    }
}