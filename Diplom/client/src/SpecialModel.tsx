import DropBoxModel from './DropBoxModel';
import {useAppSelector} from './store/hook';

interface ModelComponent {
    header: string
    imgUrl: string
    altImg: string
  }
  
const listOfModels: ModelComponent[] = [
    {
      header: 'Цветочные натюрморты',
      imgUrl: 'https://cs3.livemaster.ru/zhurnalfoto/e/9/4/130910085109.jpg',
      altImg: 'цветочный натюрморт',
    },
    {
      header: 'Ученые натюрморты',
      imgUrl: 'http://img1.liveinternet.ru/images/attach/c/2//69/891/69891399_Adrian_van_utreht_natyurmort_s_buketom_i_cherepom.jpg',
      altImg: 'суета сует',
    },
    {
      header: 'Натюрморты застолья',
      imgUrl: 'https://veryimportantlot.com/uploads/over/files/%D0%9D%D0%BE%D0%B2%D0%BE%D1%81%D1%82%D0%B8/2020/%D0%9C%D0%B0%D1%80%D1%82%202020/%D0%A4%D0%B5%D0%B2%D1%80%D0%B0%D0%BB%D1%8C%20%D0%A1%D1%82%D0%B0%D1%82%D1%8C%D1%8F%2036%20(1)%20%D0%93%D0%BE%D0%BB%D0%BB%D0%B0%D0%BD%D0%B4%D1%81%D0%BA%D0%B8%D0%B5%20%D0%BD%D0%B0%D1%82%D1%8E%D1%80%D0%BC%D0%BE%D1%80%D1%82%D1%8B.%20%D0%9A%D0%BE%D1%80%D0%BD%D0%B5%D0%BB%D0%B8%D1%81%20%D0%9C%D0%B0%D1%85%D1%83.%20%C2%AB%D0%9D%D0%B0%D1%82%D1%8E%D1%80%D0%BC%D0%BE%D1%80%D1%82%20%D1%81%20%D1%84%D1%80%D1%83%D0%BA%D1%82%D0%B0%D0%BC%D0%B8%20%D0%B8%20%D0%BF%D1%80%D0%B8%D0%B3%D0%BE%D1%82%D0%BE%D0%B2%D0%BB%D0%B5%D0%BD%D0%BD%D1%8B%D0%BC%20%D0%BB%D0%BE%D0%B1%D1%81%D1%82%D0%B5%D1%80%D0%BE%D0%BC%C2%BB.jpg',
      altImg: 'натюрморт застолья',
    },
]

function SpecialModel() {
    const {bool} = useAppSelector(state => state.mouseEventSlice)
    const topMargin: string = bool ? "": " spModel"
    
    return (
        <div className={'flex flex-col w-[96%] absolute top-[32px] transAddition' + topMargin}>
            <div className='rounded bg-white w-full shadow-lg mb-4 text-center font-serif font-bold text-2xl p-4'>Поиск символов на узконаправленных моделях</div>
            <div className='flex justify-between'>
                {listOfModels.map((item, index) => <DropBoxModel key={index} header={item.header} imgUrl={item.imgUrl} altImg={item.altImg} />)}
            </div>
        </div>
    );
}

export default SpecialModel;