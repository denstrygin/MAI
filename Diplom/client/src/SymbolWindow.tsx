import { questionEventSlice } from "./store/questionEventReducer";
import { useAppDispatch, useAppSelector } from "./store/hook";
import './animation.css';

function SymbolWindow() {
    const {visible, isLoading, data, error} = useAppSelector(state => state.questionEventSlice)
    const {setVisible} = questionEventSlice.actions;
    const dispatch = useAppDispatch()
    let animationClasses: string = 'transAddition top-[20%] right-[-40vh] h-[50vh] w-[40vh] absolute bg-white shadow-lg z-10 rounded-l p-4 border-2 border-r-0 border-gray-dark'
    visible && (animationClasses += ' animModalWindow')

    return (
        <div className={animationClasses}>
            <span className="font-bold text-black">Список определяемых моделью символов</span>
            <div className="mt-1 overflow-y pl-6 w-[90%] h-full text-lg border-solid border-t-[1px] border-black text-black">
                {isLoading
                    ? <div className="w-full h-full flex justify-center items-center"><img src={require('./img/loading.gif')} alt="загрузка..." /></div>
                    : (!!error
                        ? <span className="text-red font-bold">{error}</span>
                        : <ul className="list-disc"></ul>)
                }
            </div>
            <img onClick={e => dispatch(setVisible(false))} className="w-[30px] h-[30px] absolute top-0 right-0 cursor-pointer" src="https://cdn-icons-png.flaticon.com/512/8212/8212742.png" alt="X" />
        </div>
    );
}

export default SymbolWindow;