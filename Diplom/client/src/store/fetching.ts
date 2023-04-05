import axios from "axios";
import { questionEventSlice } from "./questionEventReducer";
import { AppDispatch } from "./store";

export const fetchData = (id: number) => async (dispatch: AppDispatch) => {
    try {
        dispatch(questionEventSlice.actions.setVisibleSegmentFetching(id))
        const response = await axios.get(`http://127.0.0.1:5000/list_of_segments?id=${id}`)
        dispatch(questionEventSlice.actions.segmentFetchingSuccess(response.data))
    } catch (error: any) {
        dispatch(questionEventSlice.actions.segmentFetchingError(error.message))    
    }
}

export const fetchImg = (id: number, imgs: []) => (dispatch: AppDispatch) => {
    try {
        
    } catch (error) {
        
    }
}