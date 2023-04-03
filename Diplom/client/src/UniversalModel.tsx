import InputText from "./InputFile";
import { useAppDispatch, useAppSelector } from "./store/hook";
import { questionEventSlice } from "./store/questionEventReducer";
import './animation.css';

function UniversalModel() {
    const imgs: {url: string, alt: string}[] = [
        {
            url: "https://cdn-s-static.arzamas.academy/uploads/ckeditor/pictures/7828/content_de_Heem.jpg",
            alt: "цветочный натюрморт",
        },
        {
            url: "https://i0.wp.com/trv-science.ru/uploads/219-0041.jpg",
            alt: "ученый натюрморт",
        },
        {
            url: "https://cdn-s-static.arzamas.academy/uploads/ckeditor/pictures/7832/content_Heda.jpg",
            alt: "натюрморт затсолья",
        },
        {
            url: "https://cs3.livemaster.ru/zhurnalfoto/3/e/c/130910085109.jpg",
            alt: "цветочный натюрморт",
        },
        {
            url: "https://veryimportantlot.com/uploads/over/files/%D0%9D%D0%BE%D0%B2%D0%BE%D1%81%D1%82%D0%B8/2020/%D0%9D%D0%BE%D1%8F%D0%B1%D1%80%D1%8C%202020/%D0%A1%D1%82%D0%B0%D1%82%D1%8C%D1%8F%20%D0%B4%D0%BB%D1%8F%20%D0%B1%D0%BB%D0%BE%D0%B3%D0%B0.%20%D0%96%D0%B8%D0%B2%D0%BE%D0%BF%D0%B8%D1%81%D1%8C%2020%20(2.4)%20%D0%92%D0%B0%D0%BD%D0%B8%D1%82%D0%B0%D1%81.%20%D0%AD%D0%B4%D0%B2%D0%B0%D1%80%D0%B4%20%D0%9A%D0%BE%D0%BB%D0%BB%D0%B8%D0%B5%D1%80.%20%D0%92%D0%B0%D0%BD%D0%B8%D1%82%D0%B0%D1%81%20%D1%81%20%D0%BA%D0%BD%D0%B8%D0%B3%D0%B0%D0%BC%D0%B8%2C%20%D1%80%D1%83%D0%BA%D0%BE%D0%BF%D0%B8%D1%81%D1%8F%D0%BC%D0%B8%20%D0%B8%20%D1%87%D0%B5%D1%80%D0%B5%D0%BF%D0%BE%D0%BC%2C%201663.jpg",
            alt: "ученый натюрморт",
        },
        {
            url: "https://veryimportantlot.com/uploads/over/files/%D0%9D%D0%BE%D0%B2%D0%BE%D1%81%D1%82%D0%B8/2020/%D0%9C%D0%B0%D1%80%D1%82%202020/%D0%A4%D0%B5%D0%B2%D1%80%D0%B0%D0%BB%D1%8C%20%D0%A1%D1%82%D0%B0%D1%82%D1%8C%D1%8F%2036%20(3)%20%D0%93%D0%BE%D0%BB%D0%BB%D0%B0%D0%BD%D0%B4%D1%81%D0%BA%D0%B8%D0%B5%20%D0%BD%D0%B0%D1%82%D1%8E%D1%80%D0%BC%D0%BE%D1%80%D1%82%D1%8B.%20%D0%9B%D0%BE%D1%80%D0%B5%D0%BD%20%D0%9A%D1%80%D1%8D%D0%B9%D0%BD.%20%C2%AB%D0%9D%D0%B0%D1%82%D1%8E%D1%80%D0%BC%D0%BE%D1%80%D1%82%20%D1%81%20%D1%84%D1%80%D1%83%D0%BA%D1%82%D0%B0%D0%BC%D0%B8%2C%20%D0%BA%D0%B8%D1%82%D0%B0%D0%B9%D1%81%D0%BA%D0%B8%D0%BC%20%D1%84%D0%B0%D1%80%D1%84%D0%BE%D1%80%D0%BE%D0%B2%D1%8B%D0%BC%20%D1%81%D0%BE%D1%81%D1%83%D0%B4%D0%BE%D0%BC%20%D0%B8%20%D1%80%D1%8B%D0%B1%D0%BE%D0%B9%C2%BB.jpg",
            alt: "натюрморт затсолья",
        },
    ]
    const {bool} = useAppSelector(state => state.mouseEventSlice)
    const {setVisible} = questionEventSlice.actions;
    const dispatch = useAppDispatch()
    const topMargin: string = bool ? " unModel" : ""

    return (
        <div className={"flex flex-col font-serif items-center w-[96%] bg-white rounded shadow-lg h-[580px] p-4 absolute transAddition top-[32px]" + topMargin}>
            <div className='flex items-baseline'>
                <span className="font-bold text-2xl">Универсальный поиск символов на голландском натюрморте</span>
                <img onClick={e => dispatch(setVisible(true))} className='ml-[10px] w-[20px] h-[20px] cursor-pointer' src="https://cdn-icons-png.flaticon.com/512/41/41943.png" alt="?" />
            </div>
            <InputText />
            <span className='font-bold'>Пример тематических изображений</span>
            <div className='flex justify-center max-w-[90%] h-[34%] overflow-x-auto'>
                {imgs.map((img, index) => <img 
                    key={index}
                    src={img.url}
                    alt={img.alt}
                />)}
            </div>
        </div>
    );
}

export default UniversalModel;