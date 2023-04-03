import {useState} from 'react';

function InputText() {
    const [drag, setDrag] = useState(0)
    function timeOut() {
        setDrag(0)
    }
    function dragHandler(e: any) {
        e.preventDefault()
        setDrag(1)
    }
    function dragLeaveHandler(e: any) {
        e.preventDefault()
        setDrag(0)
    }
    function onDropHandler(e: any) {
        e.preventDefault()
        let flag: boolean = true
        let files = [...e.dataTransfer.files]
        files.forEach(el => {
            let substr4: string = el.name.substring(el.name.length - 4)
            let substr5: string = el.name.substring(el.name.length - 5)
            if (substr4 !== ".png" && substr4 !== ".jpg" && substr5 !== ".jpeg") {
                flag = false
            }
        })
        if (flag) {
            setDrag(0)
            console.log(files)
        } else {
            setDrag(2)
            setTimeout(timeOut, 3000)
        }
    }
    function onChangeHander(e: any) {
        e.preventDefault()
        let files = [...e.target.files]
        console.log(files)
    }


    if (drag === 1) {
        return (<label 
            className="w-[80%] h-[250px] cursor-pointer flex justify-center items-center bg-gray-light border-dashed border-gray-dark border-2 rounded text-gray-dark text-center brightness-90"
            onDragStart={e => dragHandler(e)}
            onDragLeave={e => dragLeaveHandler(e)}
            onDragOver={e => dragHandler(e)}
            onDrop={e => onDropHandler(e)}
        >
            Отпустите файл, чтобы загрузить его
        </label>);
    } else if (drag === 0) {
        return (<label 
            className="w-[80%] h-[250px] cursor-pointer flex justify-center items-center bg-gray-light border-dashed border-gray-dark border-2 rounded text-gray-dark text-center"
            onDragStart={e => dragHandler(e)}
            onDragLeave={e => dragLeaveHandler(e)}
            onDragOver={e => dragHandler(e)}
        >
            Выберете файл или перетащите его в область
            <input className='hidden' onChange={e => onChangeHander(e)} type="file" multiple accept='image/png, image/jpeg'/>
        </label>);
    } else {
        return (<label 
            className="w-[80%] h-[250px] cursor-pointer flex justify-center items-center bg-gray-light border-dashed border-red border-2 rounded text-red text-center"
            onDragStart={e => dragHandler(e)}
            onDragLeave={e => dragLeaveHandler(e)}
            onDragOver={e => dragHandler(e)}
        >
            Файлы должны иметь расширение jpeg, jpg или png
            <input className='hidden' onChange={e => onChangeHander(e)} type="file" multiple accept='image/png, image/jpeg'/>
        </label>);
    }
}

export default InputText;