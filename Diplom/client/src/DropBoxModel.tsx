import InputText from './InputFile';
import {useAppDispatch} from './store/hook';
import {questionEventSlice} from './store/questionEventReducer';

function DropBoxModel({header, imgUrl, altImg}: {header: string, imgUrl: string, altImg: string}) {
    const {setVisible} = questionEventSlice.actions;
    const dispatch = useAppDispatch()

    return (
        <div className="flex flex-col items-center w-[30%] bg-white rounded shadow-lg p-4">
            <div className='flex items-baseline'>
                <span className="font-bold text-2xl">{header}</span>
                <img className='ml-[10px] w-[20px] h-[20px] cursor-pointer' onClick={e => dispatch(setVisible(true))} src="https://cdn-icons-png.flaticon.com/512/41/41943.png" alt="?" />
            </div>
            <InputText />
            <span className='font-bold'>Пример тематического изображения</span>
            <img className="max-w-[95%] max-h-[200px]" src={imgUrl}
                alt={altImg}
            />
        </div>
    );
}

export default DropBoxModel;