const car = {
    "brand": "BMW",
    "wheels": 4,
    "doors": 2,
    "type": "Sedan"
}

let JSONtoString = JSON.stringify(car)

console.log(JSONtoString)

let stringToJSON = JSON.parse(JSONtoString)

console.log(stringToJSON)