import {createSlice, PayloadAction} from '@reduxjs/toolkit'

interface DragEventState {
    isLoading: boolean
    error: string
    id: null | string
    data: any
}

const initialDragEvent: DragEventState = {
    isLoading: false,
    error: '',
    id: null,
    data: []
}

export const dragEventSlice = createSlice({
    name: 'dragEvent',
    initialState: initialDragEvent,
    reducers: {
        
    }
})

export default dragEventSlice.reducer;